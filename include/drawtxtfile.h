#ifndef DRAW_TXT_FILE
#define DRAW_TXT_FILE


#include <Arduino.h>
#include <DisplayConfig.h>
#include <UserInputs.h>
#include <drawFileMenu.h>



int utf8CharLen(char c);

void draw_text_file(char* directory, char* page_buffer);

int utf8CharLen(char c) {
    if ((c & 0x80) == 0) return 1;        // 1 байт 
    else if ((c & 0xE0) == 0xC0) return 2; // 2 
    else if ((c & 0xF0) == 0xE0) return 3; // 3 
    else if ((c & 0xF8) == 0xF0) return 4; // 4 
    return 1; 
}
void draw_text_file(char* directory, char* page_buffer) {
    unsigned long CurrentTime = millis();
    static unsigned long timer_1 = 0;

    if (CurrentTime - timer_1 >= 50) {
        drawState.result = draw_selecting_icon(0);
        u8g2.enableUTF8Print();
        u8g2.clearBuffer();
        draw_directory_info(directory);
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);

        byte x = 0;
        byte y = 20;
        int chars_in_row = 0; 
        int rows_on_screen = 0; 

        while (*page_buffer != '\0') {
            if (rows_on_screen >= 5) { 
                break;
            }

            if (chars_in_row >= 26) {
                x = 0;
                y += 10; 
                chars_in_row = 0; 
                rows_on_screen++; 
                page_buffer++;   
            }

            char current_char[5] = {0}; 
            int char_len = utf8CharLen(*page_buffer);
            strncpy(current_char, page_buffer, char_len);
            u8g2.setCursor(x, y);
            u8g2.print(current_char);
            chars_in_row++;

            page_buffer += char_len;

            // Для ASCII 
            if ((unsigned char)current_char[0] <= 127) {
                x += 5; 
            } else { 
                // Для кириличних 
                x += u8g2.getUTF8Width(current_char) + 1; 
            }
        }

        u8g2.sendBuffer();
        yield();
    }
}


#endif