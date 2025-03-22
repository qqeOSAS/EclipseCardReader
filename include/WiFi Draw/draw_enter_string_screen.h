#ifndef DRAW_ENTER_SCREEN
#define DRAW_ENTER_SCREEN


#include <Arduino.h>
#include <DisplayConfig.h>
#include <UserInputs.h>
#include <drawFileMenu.h>
#include <utils/String_utils.h>

struct selectedChar{
    bool isSelected;
    char charValue;
};
struct selected_icon_pos{
    byte next_keyboard_page;
    int x;
    int y;
};

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
selected_icon_pos draw_select_icon(int command) {
    selected_icon_pos icon_pos = {0, 0, 0};

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
            icon_pos.next_keyboard_page = 2; // Indicate previous page
        }
    }

    // Handle wrapping when moving right
    if (select_icon_x > 98) {
        select_icon_x = -2; // Wrap to the far left
        select_icon_y += 10; // Move down a row
        if (select_icon_y > 52) {
            select_icon_y = 32; // Wrap to the top row
            icon_pos.next_keyboard_page = 1; // Indicate next page
        }
    }

    // Set the x and y positions in the structure
    icon_pos.x = select_icon_x;
    icon_pos.y = select_icon_y;

    // Draw the selection icon
    u8g2.drawFrame(select_icon_x, select_icon_y, 10, 10);
    return icon_pos;
}

selectedChar return_select_char(int command,byte page_num,selected_icon_pos icon_pos){
    selectedChar selected_char = {false,0};
    byte symbols_per_page = 34;
    int corrector = (page_num - 1) * symbols_per_page;
    float selected_char_index = 0;

    if(icon_pos.x < 0 )
        icon_pos.x = 0;

    if(command == SELECT){
        selected_char.isSelected = true;
        switch(icon_pos.y){
            case 32:
                selected_char_index = round((icon_pos.x + 2) / 10);
                break;
            case 42:
                selected_char_index = round(11 + float(icon_pos.x) / 10);                
                break;
            case 52:
                selected_char_index = round(22 + float(icon_pos.x) / 10);
                break;
        }
        selected_char.charValue = keyboard_chars[corrector + int(selected_char_index)];
    }

    return selected_char;

}


//returns page number
byte draw_keyboard(byte next_page){
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

    return page_num;

}

void draw_enter_string_screen(char* up_label){
    static char entered_string[30] = "";

    u8g2.clearBuffer();
    u8g2.setColorIndex(1);
    u8g2.setFont(u8g2_font_NokiaSmallBold_tr);

    u8g2.setCursor(2,10);
   // u8g2.print(up_label);
    draw_directory_info("Enter SSID pasord");
    u8g2.drawRFrame(0,15,128,15,2);
    u8g2.drawXBMP(108,30,20,34,enter_char_panel);

    byte command = serial_command();

    selected_icon_pos icon_pos = draw_select_icon(command);
    byte keyboard_page = draw_keyboard(icon_pos.next_keyboard_page);
    selectedChar selected_char = return_select_char(command,keyboard_page,icon_pos);
    if(selected_char.isSelected)
        add_char(entered_string,selected_char.charValue,sizeof(entered_string));
    Serial.println(entered_string);


    u8g2.sendBuffer();
}











#endif