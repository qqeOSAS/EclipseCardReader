#ifndef USER_INPUTS_FILE_PROPERTIES
#define USER_INPUTS_FILE_PROPERTIES

#include <Arduino.h>
#include <UserInputs.h>
#include <DisplayConfig.h>
#include <SdCard_utils.h>

#define OK 0
#define ACTIONS 1

struct selected_user_option {
    bool is_selected = false;
    byte selected_option = 0;
};

selected_user_option draw_files_properties_menu_user(int command,char* button_1_label, char* button_2_label) {
    selected_user_option user_option = {false, 0};
    static int8 selected_icon = 0;


    switch (command) {
        case SELECT:
            user_option.is_selected = true;
            user_option.selected_option = selected_icon;
            break;
        case LIST_DOWN_MENU:
            selected_icon++;
            if (selected_icon > 1) selected_icon = 0;break;
        case LIST_UP_MENU:
            selected_icon--;
            if (selected_icon < 0) selected_icon = 1;break;
    }

    u8g2.setColorIndex(1);
    u8g2.drawBox(0, 53, 128, 14);

    u8g2.setColorIndex(0); // Set color index to 1 before drawing the frames and text
    switch (selected_icon) {
        case 0:
            u8g2.drawRFrame(-2, 52, 64, 12, 4); break;
        case 1:
            u8g2.drawRFrame(64, 52, 68, 12, 4); break;
    }

    u8g2.setFont(u8g2_font_nokiafc22_tr);
    u8g2.setFontMode(1);
    u8g2.setCursor(30, 62);
    u8g2.print(button_1_label);
    u8g2.setCursor(70, 62);
    u8g2.print(button_2_label);

    return user_option;
}
void draw_properties_(FileProperties* file_properties){
    u8g2.setColorIndex(1);
    u8g2.setFont(u8g2_font_5x8_t_cyrillic);

    u8g2.setCursor(0,20); u8g2.print("File name: "); u8g2.print(file_properties->name);
    u8g2.drawLine(0,21,128,21);

    u8g2.setCursor(0,30); u8g2.print("File size: "); u8g2.print(file_properties->size); u8g2.print(" bytes");
    u8g2.drawLine(0,31,128,31);

    u8g2.setCursor(0,40); u8g2.print("Created:"); 
    u8g2.print(file_properties->creation_time_day);
    u8g2.print(".");
    u8g2.print(file_properties->creation_time_month);
    u8g2.print(".");
    u8g2.print(file_properties->creation_time_year);
    u8g2.print(" ");
    u8g2.print(file_properties->creation_time_hours);
    u8g2.print(":");
    u8g2.print(file_properties->creation_time_minutes);

    u8g2.drawLine(0,41,128,41);

    u8g2.setCursor(0,50); u8g2.print("Attributes: ");
    switch (file_properties->attributes){
        case 0x00:
            u8g2.print("Normal");break;
        case 0x01:
            u8g2.print("Read only");break;
        case 0x02:
            u8g2.print("Hidden");break;
        case 0x04:
            u8g2.print("System");break;
        case 0x08:
            u8g2.print("Volume label");break;
        case 0x10:
            u8g2.print("Directory");break;
        case 0x16:
            u8g2.print("Dir.Hiden.Sys");break;
        case 0x20:
            u8g2.print("Archive");break;
        case 0x22:
            u8g2.print("Archive and hidden");break;
        case 0x30:
            u8g2.print("Long file name");break;
    }
        u8g2.drawLine(0,51,128,51);
}

#endif
