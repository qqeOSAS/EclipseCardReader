#ifndef READ_TXT
#define READ_TXT

#include <SDCardConfig.h>

bool isTextFile(const char* filepath);
void readTextFile(char* filename, byte page);


bool isTextFile(const char* filepath) {
    const char* ext = strrchr(filepath, '.'); // Знаходимо останню крапку у шляху
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

void readTextFile(char* filename, byte page) {
    SdFile file;

    // Обчислюємо позицію для зчитування, залежно від сторінки
    int position = (page - 1) * 130;
    
    // Перевіряємо, чи файл існує
    if (!sd.exists(filename)) {
        Serial.print("File does not exist: ");
        Serial.println(filename);
        return;
    }

    // Відкриваємо файл для читання
    if (!file.open(filename, O_READ)) {
        Serial.print("Failed to open file: ");
        Serial.println(filename);
        return;
    }

    byte array_index = 0;
    
    // Перевіряємо, чи є дані для поточної сторінки
    file.seekSet(position);  // Встановлюємо позицію для зчитування з початку поточної сторінки
    while (file.available() && array_index < 130) {
        int c = file.read();
        if (c != -1) {  // Перевіряємо, чи не досягнуто кінця файлу
            char character = (char)c;
            text_file_page_buffer[array_index] = character;
            array_index++;
            Serial.print(character);
        } else {
            break;  // Якщо файл завершився, зупиняємо зчитування
        }
    }

    // Якщо на поточну сторінку менше 130 символів, заповнюємо залишок порожніми символами
    if (array_index < 130) {
        for (int i = array_index; i < 130; i++) 
            text_file_page_buffer[i] = '\0';  // Заповнюємо порожні місця
        
    }

    file.close();
    Serial.println("\nFile read complete.");
}


#endif