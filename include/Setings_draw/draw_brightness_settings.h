#ifndef draw_brightness_settings_h
#define draw_brightness_settings_h

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <Setings/Diplay_brigthnes_setting.h>
#include <Bitmaps_headers/Bitmaps.h>
#include <File properties browser/draw_file_properties_utils.h>
#include <EEPROM_manager/eeprom_utils.h>

void draw_brightness_slider(int input_brightness,bool changing_values) {
    int slider_position = map(input_brightness, 0, 255, 64, 120); // Map brightness to slider position
    u8g2.drawBox(64,30,56,2); // Draw slider
    u8g2.drawDisc(slider_position, 31, 4, U8G2_DRAW_ALL); // Draw slider knob
    if(changing_values){
        u8g2.setColorIndex(0);
        u8g2.drawCircle(slider_position, 31, 2); // Draw outline of the knob
        u8g2.setColorIndex(1);
    }
}

void draw_brightness_settings(int input_brightness) {

    u8g2.setColorIndex(1);
    draw_directory_info(" BRIGHTNESS SETTINGS. Lover brightness - less power consumption More operation time!");

    int brightness_percent = (input_brightness * 100) / 255;
    byte icon_num = map(brightness_percent, 0, 100, 0, 3);
     // Map brightness percentage to icon index
    u8g2.drawXBMP(7,22,20,20,epd_bitmap_brightness_icons_20X20[icon_num]); // Draw brightness icon based on percentage
    u8g2.setFont(u8g2_font_nokiafc22_tr);
    u8g2.setCursor(35, 39);
    u8g2.printf("%d%%", brightness_percent);


 
}
void draw_bar(){
    u8g2.drawBox(0, 53, 128, 14);
    u8g2.setColorIndex(0); // Set color index to 1 before drawing the frames and text
    u8g2.setFont(u8g2_font_nokiafc22_tr);
    u8g2.setFontMode(1);
    u8g2.setCursor(30, 62);
    u8g2.print("Back");
    u8g2.setCursor(70, 62);
    u8g2.print("Save");
    u8g2.setColorIndex(1); // Reset color index to default

    
}


void display_brightness_settings() {
    int setted_brightness = display_settings_eeprom.brightness; // Default brightness value
    selected_user_option user_option = {false, 0};
    bool changing_values = true;
    while(1){
        ESP.wdtDisable();
        u8g2.clearBuffer();


        int command = serial_command();
        if(command == BACK)
            changing_values = !changing_values; // Toggle changing values on select
        
        draw_brightness_settings(setted_brightness);
        draw_brightness_slider(setted_brightness,changing_values);

        if(!changing_values)
            user_option = draw_files_properties_menu_user(command, "Back", "Save");
        else{
            change_brightness(&setted_brightness, command);
            draw_bar();
        }

        if(user_option.is_selected){
            switch(user_option.selected_option){
                case 0: // Back
                    return;
                case 1: // Save
                    display_settings_eeprom.brightness = setted_brightness; // Save brightness setting
                    eeprom_save_struct(DISPLAY_SETTINGS_EEPROM_ADDRESS, display_settings_eeprom); // Save to EEPROM
                    return;
            }
        }
        


        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    }
    
}





#endif // draw_brightness_settings_h