#ifndef DISPLAY_INTERFACE_H
#define DISPLAY_INTERFACE_H


#include <DisplayConfig.h>
#include <UserInputs.h>
struct user_choice{
    bool is_selected = false;
    byte selected_option = 0;   
};
#define DELETE 0
#define CANCEL 1


user_choice draw_select_two_options_menu(int command,char* filename, char* button_label1, char* button_label2){
    user_choice user_choice = {false, 0};
    static int8 selected_icon = 0;

    switch (command) {
        case SELECT:
            user_choice.is_selected = true;
            user_choice.selected_option = selected_icon;
            break;
        case LIST_DOWN_MENU:
            selected_icon++;
            if (selected_icon > 1) selected_icon = 0;break;
        case LIST_UP_MENU:
            selected_icon--;
            if (selected_icon < 0) selected_icon = 1;break;
    }
    u8g2.setColorIndex(1);
    u8g2.drawRBox(0, 40, 128, 24,5);
    u8g2.setColorIndex(0);

    switch (selected_icon) {
        case 0:
            u8g2.drawRFrame(3, 42, 122, 12, 4); break;
        case 1:
            u8g2.drawRFrame(3, 52, 122, 12, 4); break;
    }
    u8g2.setFont(u8g2_font_NokiaSmallBold_tr);
    u8g2.setCursor(15, 62);
    u8g2.print(button_label1);
    u8g2.setFontMode(1);
    u8g2.setCursor(10, 51);
    u8g2.print(button_label2);
    u8g2.setFont(u8g2_font_5x8_t_cyrillic);
    u8g2.print(filename);

    return user_choice;
}











#endif






