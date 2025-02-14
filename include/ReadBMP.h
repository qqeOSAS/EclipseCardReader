// This file contains functions for reading and processing BMP files on an SD card and displaying the image in a monochrome format. 
//The `read_BMP()` function reads the BMP file header, validates the file format, and processes the pixel data into a 1-bit-per-pixel format suitable for display on a screen
// displays a 24-bit BMP file as a monochrome image.


// NOTE: The current implementation has some limitations and does not fully handle 
// all BMP formats or display correctly in all cases. Improvements and bug fixes 
// will be made to address these issues and ensure proper functionality in the future.


#ifndef READ_BMP
#define READ_BMP

#include <SDCardConfig.h>
#include <DisplayConfig.h>

struct __attribute__((packed)) BMPFileHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
};

struct __attribute__((packed)) BMPInfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitDepth;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t importantColors;
};


uint8_t reverseByte(uint8_t byte) {
    byte = (byte & 0xF0) >> 4 | (byte & 0x0F) << 4;
    byte = (byte & 0xCC) >> 2 | (byte & 0x33) << 2;
    byte = (byte & 0xAA) >> 1 | (byte & 0x55) << 1;
    return byte;
}

void convertBMPto1BPP(uint8_t* bmpData, uint8_t* outputData, int width, int height) {
    int bmpHeaderSize = 54;
    int bmpRowSize = (width * 3 + 3) & ~3;
    int outputIndex = 0;

    for (int y = 0; y < height; y++) {  
        for (int x = 0; x < width; x += 8) {
            uint8_t byte = 0;
            for (int bit = 0; bit < 8; bit++) {
                if (x + bit < width) {
                    int bmpIndex = bmpHeaderSize + (height - 1 - y) * bmpRowSize + (x + bit) * 3;
                    uint8_t b = bmpData[bmpIndex];
                    uint8_t g = bmpData[bmpIndex + 1];
                    uint8_t r = bmpData[bmpIndex + 2];

                    uint8_t gray = (r + g + b) / 3;
                    if (gray < 128) {  
                        byte |= (1 << (7 - bit));  
                    }
                }
            }
            outputData[outputIndex++] = byte;
        }
    }
}



bool isBMPfile(const char* filepath) {
    const char* ext = strrchr(filepath, '.'); 
    if (ext && strcasecmp(ext, ".bmp") == 0)
        return true;
    return false; 
}

void read_BMP(const char* filename) {
    SdFile bmpFile;

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    if (!bmpFile.open(filename, O_READ)) {
        Serial.print("Не вдалося відкрити файл: ");
        Serial.println(filename);
        return;
    }

    bmpFile.read(&fileHeader, sizeof(fileHeader));
    bmpFile.read(&infoHeader, sizeof(infoHeader));

    if (fileHeader.signature != 0x4D42) {
        Serial.println("Це не BMP-файл!");
        bmpFile.close();
        return;
    }


    Serial.print("BMP Width: "); Serial.println(infoHeader.width);
    Serial.print("BMP Height: "); Serial.println(infoHeader.height);
    Serial.print("Bit Depth: "); Serial.println(infoHeader.bitDepth);
    
    if (infoHeader.bitDepth != 24) {
        Serial.println("Цей BMP має бути 24-бітним!");
        bmpFile.close();
        return;
    }

    bmpFile.seekSet(fileHeader.dataOffset);
    long pixelDataSize = fileHeader.fileSize - fileHeader.dataOffset;

    uint8_t* pixelData = (uint8_t*)malloc(pixelDataSize);
    uint8_t* monoBitmap = (uint8_t*)malloc((128 * 64) / 8); 

    if (!pixelData || !monoBitmap) {
        Serial.println("Помилка виділення пам'яті!");
        bmpFile.close();
        return;
    }

    bmpFile.read(pixelData, pixelDataSize);
    convertBMPto1BPP(pixelData, monoBitmap, 128, 64);

    Serial.println("Mono Bitmap (перші 16 байтів):");
    for (int i = 0; i < 16; i++) {
        Serial.print(monoBitmap[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    while(1){
        u8g2.clearBuffer();
        u8g2.drawXBM(0, 0, 128, 64, monoBitmap);
        u8g2.sendBuffer();
    }

    free(pixelData);
    free(monoBitmap);
    bmpFile.close();
}

#endif
