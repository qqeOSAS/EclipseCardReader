#ifndef DRAW_POROPERTIES_ACTIONS
#define DRAW_POROPERTIES_ACTIONS

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <File properties browser/draw_file_properties_utils.h>
#include <File properties browser/draw_actions.h>


void draw_file_properties(char* file_name){
    FileProperties file_properties = get_file_properties(file_name);
    selected_user_option user_option = {false,0};
    while(1){
        
        ESP.wdtDisable();
        Serial.println(file_name);

        int command = serial_command();

        u8g2.clearBuffer();
        u8g2.setColorIndex(1);

        char full_path[100];
        strcpy(full_path, "File properties/");
        strcat(full_path, file_name);
        draw_directory_info(full_path);

        user_option = draw_files_properties_menu_user(command,"OK","Actions");
        draw_properties_(&file_properties);

        if(user_option.is_selected && user_option.selected_option == OK)
            break;
        if(user_option.is_selected && user_option.selected_option == ACTIONS){  
            display_properties_actions(&file_properties, file_name);
            break;
        }

          

        ESP.wdtDisable();
        u8g2.sendBuffer();
    }
}





#endif