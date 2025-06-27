#ifndef CD_CONFIG
#define CD_CONFIG

#include <Arduino.h>
#include <SdFat.h>
#include <SPI.h>

#define SD_CS_PIN 15
#define MAX_GLOBAL_DERICTORY_FILES 100
bool SD_CARD_INITIALIZATION_STATUS = false;

SdFat sd;


struct Draw_Image {
    int width;                // Ширина зображення
    int height;               // Висота зображення
    uint8_t image_buffer[1024];
    uint32 image_pages; // Буфер для зображення
};






#endif