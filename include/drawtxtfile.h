// This file contains functions for displaying and navigating through text files on a screen. 
// It handles the drawing of text content from a file, including UTF-8 encoded characters and 
// Cyrillic text supported. 
// The screen is updated periodically based on a 
// timer to ensure smooth rendering and user interaction.

#ifndef DRAW_TXT_FILE
#define DRAW_TXT_FILE


#include <Arduino.h>
#include <DisplayConfig.h>
#include <UserInputs.h>
#include <drawFileMenu.h>



int utf8CharLen(char c);

void draw_text_file(char* directory, char* page_buffer);

// Довжина UTF-8 символу в байтах
int utf8CharLen(char c) {
    if ((c & 0x80) == 0) return 1;        // 1 
    else if ((c & 0xE0) == 0xC0) return 2; // 2 
    else if ((c & 0xF0) == 0xE0) return 3; // 3 
    else if ((c & 0xF8) == 0xF0) return 4; // 4 
    return 1; 
}

//drawing txt files
void draw_text_file(char* directory, char* page_buffer) {
    unsigned long CurrentTime = millis();
    static unsigned long timer_1 = 0;

    if (CurrentTime - timer_1 >= 50) { //timer
        timer_1 = CurrentTime;

// Перевірити!!! може бути помилка тут, бо drawState.result не використовується далі
        drawState.result = draw_selecting_icon(0); 

        u8g2.enableUTF8Print();
        u8g2.clearBuffer();
        draw_directory_info(directory);
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);

        uint8_t x = 0;
        uint8_t y = 20;

        uint8_t rows_on_screen = 0; 

        while (*page_buffer != '\0') {

            if (rows_on_screen >= 5) break;
            
        
            if (*page_buffer == '\n') {
                x = 0;
                y += 10;
                rows_on_screen++;
                page_buffer++;  // перейти до наступного символу
                continue;
            }

            char current_char[5] = {0};
            int char_len = utf8CharLen(*page_buffer);
            strncpy(current_char, page_buffer, char_len);
            int char_width = u8g2.getUTF8Width(current_char);

            if (x > 0 && x + char_width > 128) {
                x = 0;
                y += 10;
                rows_on_screen++;
                if (rows_on_screen >= 5) break;
            }

            u8g2.setCursor(x, y);
            u8g2.print(current_char);
            page_buffer += char_len;
            x += char_width + 1;
        }
        
        u8g2.sendBuffer();
        yield();
    }
}


#endif