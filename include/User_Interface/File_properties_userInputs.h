#ifndef USER_INPUTS_FILE_PROPERTIES
#define USER_INPUTS_FILE_PROPERTIES

#include <Arduino.h>
#include <UserInputs.h>
#include <DisplayConfig.h>

struct selected_user_option {
    bool is_selected = false;
    byte selected_option = 0;
};

selected_user_option draw_files_properties_menu_user(int command) {
    selected_user_option user_option = {false, 0};
    static int8 selected_icon = 0;

    // Debug: Print the received command
   // Serial.print("Command received: ");
    Serial.println(command);

    switch (command) {
        case SELECT:
            user_option.is_selected = true;
            user_option.selected_option = selected_icon;
            // Debug: Print the selected option
           // Serial.print("Option selected: ");
           // Serial.println(selected_icon);
            break;
        case LIST_DOWN_MENU:
            selected_icon++;
            if (selected_icon > 1) selected_icon = 0;
            // Debug: Print the new selected icon after increment
           // Serial.print("Selected icon after LIST_DOWN_MENU: ");
           // Serial.println(selected_icon);
            break;
        case LIST_UP_MENU:
            selected_icon--;
            if (selected_icon < 0) selected_icon = 1;
            // Debug: Print the new selected icon after decrement
           // Serial.print("Selected icon after LIST_UP_MENU: ");
           // Serial.println(selected_icon);
            break;
    }

    u8g2.setColorIndex(1); // Set color index to 0 before drawing the box
    u8g2.drawRBox(0, 53, 128, 14, 4);

    u8g2.setColorIndex(0); // Set color index to 1 before drawing the frames and text
    switch (selected_icon) {
        case 0:
            u8g2.drawRFrame(0, 52, 64, 13, 4); 
            // Debug: Print the frame being drawn for case 0
            //Serial.println("Drawing frame for option 0");
            break;
        case 1:
            u8g2.drawRFrame(64, 52, 68, 13, 4); 
            // Debug: Print the frame being drawn for case 1
            //Serial.println("Drawing frame for option 1");
            break;
    }

    u8g2.setFont(u8g2_font_nokiafc22_tr);
    u8g2.setFontMode(1);
    u8g2.setCursor(30, 62);
    u8g2.print("OK");
    u8g2.setCursor(70, 62);
    u8g2.print("Delete file");

    return user_option;
}

#endif
