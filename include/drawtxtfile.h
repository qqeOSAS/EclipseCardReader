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


// Довжина UTF-8 символу в байтах
uint8_t utf8CharLen(char c) {
    if ((c & 0x80) == 0) return 1;        // 1 
    else if ((c & 0xE0) == 0xC0) return 2; // 2 
    else if ((c & 0xF0) == 0xE0) return 3; // 3 
    else if ((c & 0xF8) == 0xF0) return 4; // 4 
    return 1; 
}

// Function to handle newline characters in the text file content
bool check_newline_enter(char*& page_buffer, uint8_t& x, uint8_t& y, uint8_t& rows_on_screen) {
    if (*page_buffer != '\n') return false;
        
    x = 0;
    y += 10;
    rows_on_screen++;
    page_buffer++;
    return true;
}

// Function to check if the current character exceeds the screen width
void check_endline(uint8_t& x, uint8_t& y, uint8_t char_width, uint8_t& rows_on_screen){
    if (x > 0 && x + char_width > 128) {
        x = 0;
        y += 10;
        rows_on_screen++;
       
    }
}
void draw_character(char*& page_buffer, uint8_t& x, uint8_t& y, uint8_t& rows_on_screen){
    char current_char[5] = {0};
    uint8_t char_len = utf8CharLen(*page_buffer);
    strncpy(current_char, page_buffer, char_len);
    uint8_t char_width = u8g2.getUTF8Width(current_char);

    check_endline(x, y, char_width, rows_on_screen);
    if (rows_on_screen >= 5) return;

    u8g2.setCursor(x, y);
    u8g2.print(current_char);
    page_buffer += char_len;
    x += char_width + 1;
}



// Function to draw the text file content on the screen
void draw_text_file(char* directory, char* page_buffer) {

    unsigned long CurrentTime = millis();
    static unsigned long timer_1 = 0;

    //timer
    if (CurrentTime - timer_1 >= 50) { 
        timer_1 = CurrentTime;

        u8g2.enableUTF8Print();
        u8g2.clearBuffer();
        draw_directory_info(directory);
        
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);

        uint8_t x = 0;
        uint8_t y = 20;

        uint8_t rows_on_screen = 0; 
        // Loop through the page buffer and draw each character on the screen
        while (*page_buffer != '\0') {

            if (rows_on_screen >= 5) break;
            
            if(check_newline_enter(page_buffer, x, y, rows_on_screen)) // Handle newline 
                continue; 
            
            draw_character(page_buffer, x, y, rows_on_screen); // Draw the character
        }
        
        u8g2.sendBuffer();
        yield();
    }
}


#endif