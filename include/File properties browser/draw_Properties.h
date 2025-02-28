#ifndef DRAW_POROPERTIES_ACTIONS
#define DRAW_POROPERTIES_ACTIONS

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <File properties browser/draw_file_properties_utils.h>
#include <File properties browser/draw_actions.h>


void draw_file_properties(char* file_name){
    while(1){
        ESP.wdtDisable();
        FileProperties file_properties = get_file_properties(file_name);
        static selected_user_option user_option = {false,0};
        int command = serial_command();

        u8g2.clearBuffer();
        u8g2.setColorIndex(1);

        draw_directory_info(("File properties/" + String(file_name)).c_str());

        user_option = draw_files_properties_menu_user(command);
        draw_properties_(&file_properties);

        if(user_option.is_selected && user_option.selected_option == OK)
            break;
        if(user_option.is_selected && user_option.selected_option == ACTIONS){
            display_properties_actions();
            break;
            
        }
          
    

        ESP.wdtDisable();
        u8g2.sendBuffer();
    }
}











#endif