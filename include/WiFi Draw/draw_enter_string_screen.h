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

//returns next page
byte draw_select_icon(int command) {
    static int select_icon_x = -2;
    static int select_icon_y = 32;

    // Update the position of the selection icon based on the command
    if (command == LIST_UP_MENU) select_icon_x -= 10;
    else if (command == LIST_DOWN_MENU) select_icon_x += 10;
    

    // Handle wrapping when moving left
    if (select_icon_x < -2) {
        select_icon_x = 98; // Wrap to the far right
        select_icon_y -= 10; // Move up a row
        if (select_icon_y < 32) {
            select_icon_y = 52; // Wrap to the bottom row
            return 2; // Indicate previous page
        }
    }

    // Handle wrapping when moving right
    if (select_icon_x > 98) {
        select_icon_x = -2; // Wrap to the far left
        select_icon_y += 10; // Move down a row
        if (select_icon_y > 52) {
            select_icon_y = 32; // Wrap to the top row
            return 1; // Indicate next page
        }
    }

    // Draw the selection icon
    u8g2.drawFrame(select_icon_x, select_icon_y, 10, 10);
    return 0; // No page change
}

void draw_keyboard(byte next_page){
    const byte symbols_per_page = 34;  
    const byte page_count = 3;
    static byte page_num = 1;
    int corrector = (page_num - 1) * symbols_per_page;

    if(next_page == 1 && page_num < page_count)
        page_num++;
    if(next_page == 2 && page_num > 1)
        page_num--;
    
    u8g2.setFont(u8g2_font_5x8_t_cyrillic);
    byte x = 1;
    byte y = 40;

    for(byte i = 0; i < symbols_per_page;i++){
        byte symb_index = corrector + i;
        u8g2.setCursor(x,y);
        u8g2.print(keyboard_chars[symb_index]);
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



}

void draw_enter_string_screen(char* up_label){

    u8g2.clearBuffer();
    u8g2.setColorIndex(1);
    u8g2.setFont(u8g2_font_NokiaSmallBold_tr);

    u8g2.setCursor(2,10);
   // u8g2.print(up_label);
    draw_directory_info("Enter SSID pasord");
    u8g2.drawRFrame(0,15,128,15,2);
    u8g2.drawXBMP(108,30,20,34,enter_char_panel);

    byte command = serial_command();
    byte next_keyboard_page = draw_select_icon(command);
    draw_keyboard(next_keyboard_page);




    u8g2.sendBuffer();
}











#endif