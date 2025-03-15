#ifndef DRAW_ENTER_SCREEN
#define DRAW_ENTER_SCREEN


#include <Arduino.h>
#include <DisplayConfig.h>
#include <UserInputs.h>
#include <drawFileMenu.h>

char keyboard_chars[] = {
    // Цифри
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    
    // Великі літери
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

    // Малі літери
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

    // Символи пунктуації та спеціальні символи
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', 
    '[', ']', '{', '}', '\\', '|', ';', ':', '\'', '"', ',', '.', '/', '<', '>', '?', '`', '~',

    // Пробіл
    ' '
};



void draw_enter_string_screen(char* up_label){
    u8g2.clearBuffer();
    u8g2.setColorIndex(1);
    u8g2.setFont(u8g2_font_NokiaSmallBold_tr);

    u8g2.setCursor(2,10);
   // u8g2.print(up_label);
    draw_directory_info("Enter SSID pasord");
    u8g2.drawRFrame(0,15,128,15,2);
    u8g2.drawXBMP(108,30,20,34,enter_char_panel);
    

    u8g2.setFont(u8g2_font_5x8_t_cyrillic);
    byte x = 0;
    byte y = 40;
    for(byte i = 0; i < 34;i++){
        u8g2.setCursor(x,y);
        u8g2.print(keyboard_chars[i]);
        x += 10;
        if(x > 108){
            x = 0;
            y += 10;
        }
        if(y > 64){
            x = 0;
            y = 40;
        }
            
        
    }
    u8g2.sendBuffer();
    


}











#endif