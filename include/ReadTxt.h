// This file contains functions for reading text-based files (.txt, .log, .csv, .ini) from an SD card. 

// It reads 130 characters per page, which can be displayed or processed further. 
// prints the characters read to the serial monitor for debugging purposes. 



#ifndef READ_TXT
#define READ_TXT

#include <SDCardConfig.h>

bool isTextFile(const char* filepath);
int readTextFile(char* filename, uint32_t page, char* text_file_page_buffer);

const char* TEXT_FILE_EXTENSIONS[] = {
    ".txt", ".log", ".csv", ".ini", ".md", ".json", ".xml", ".yaml", ".yml", ".cfg", ".conf", ".lst", ".dat", ".gcode", ".h",".c",".py",".cpp",
};


bool isTextFile(const char* filepath) {
    const char* ext = strrchr(filepath, '.'); 
    if (ext) {
        for(byte i = 0; i < 18;i++){
            if(strcasecmp(ext, TEXT_FILE_EXTENSIONS[i]) == 0) {
                return true; 
            }
        }
    }
    return false; 
}

// page З нуля передавати
int readTextFile(char* filename, uint32_t page, char* text_file_page_buffer) {
    SdFile file;

    text_file_page_buffer[0] = '\0';

    if (!sd.exists(filename)) {
        Serial.print("File does not exist: ");
        Serial.println(filename);
        return -1;
    }

    if (!file.open(filename, O_READ)) {
        Serial.print("Failed to open file: ");
        Serial.println(filename);
        return -1;
    }

    uint64_t fileSize = file.fileSize();
    uint32_t file_pages = (fileSize + 129) / 130;

    uint16_t array_index = 0;
    
    file.seekSet(page * 130UL);
    while (file.available() && array_index < 130) {
        int c = file.read();
        if (c != -1) { 
            char character = (char)c;
            text_file_page_buffer[array_index] = character;
            array_index++; 
            Serial.print(character);
        } else {
            break;  
        }
    }

   
    text_file_page_buffer[array_index] = '\0';

    file.close();
    Serial.println("\nFile read complete.");
    return file_pages;
}


#endif