// This file contains functions for reading text-based files (.txt, .log, .csv, .ini) from an SD card. 

// It reads 130 characters per page, which can be displayed or processed further. 
// prints the characters read to the serial monitor for debugging purposes. 



#ifndef READ_TXT
#define READ_TXT

#include <SDCardConfig.h>

bool isTextFile(const char* filepath);
int readTextFile(char* filename, byte page,char* text_file_page_buffer);


bool isTextFile(const char* filepath) {
    const char* ext = strrchr(filepath, '.'); 
    if (ext) {
        if (strcasecmp(ext, ".txt") == 0 || 
            strcasecmp(ext, ".log") == 0 || 
            strcasecmp(ext, ".csv") == 0 || 
            strcasecmp(ext, ".ini") == 0) {
            return true;
        }
    }
    return false; 
}


int readTextFile(char* filename, byte page, char* text_file_page_buffer) {
    SdFile file;


    int position = (page - 1) * 130;
    

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
    uint32_t fileSize = file.fileSize();
    int file_pages = (fileSize + 129) / 130;


    byte array_index = 0;
    
    file.seekSet(position);  
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

   
    if (array_index < 130) {
        for (int i = array_index; i < 130; i++) 
            text_file_page_buffer[i] = '\0';  
        
    }

    file.close();
    Serial.println("\nFile read complete.");
    return file_pages;
}


#endif