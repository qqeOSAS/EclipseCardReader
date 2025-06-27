#ifndef Brightness_Settings_H
#define Brightness_Settings_H


#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <UserInputs.h>
#include <EEPROM_manager/eeprom_utils.h>

void set_brightness(int brightness) {
    u8g2.setContrast(brightness);
}
void change_brightness(int* input_brightness,int command) {
    switch (command) {
        case LIST_UP_MENU:
            if (*input_brightness < 255) 
                *input_brightness += 10; // Increase brightness by 5
            break;
        case LIST_DOWN_MENU:
            if (*input_brightness > 0) 
                *input_brightness -= 10; // Decrease brightness by 5
            break;
    }
    if(*input_brightness > 255) 
        *input_brightness = 255;
    if(*input_brightness < 0)
        *input_brightness = 2; // Ensure brightness does not go below 
    set_brightness(*input_brightness);
}
void apply_display_EEPROM_settings(){
    u8g2.setContrast(display_settings_eeprom.brightness);
}















#endif // Brightness_Settings_H