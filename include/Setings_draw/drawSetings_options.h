#ifndef DRAW_SETTINGS_OPTIONS_H
#define DRAW_SETTINGS_OPTIONS_H

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <Bitmaps_headers/Bitmaps.h>
#include "draw_brightness_settings.h"

DrawOptionsState drawSettingsState;
char settings_options[][30] = {"Display Brightness", "SD Card Settings", "System Settings", "About"};


void draw_setings_options(){
    u8g2.setColorIndex(1);
    draw_directory_info(" SETTINGS OPTIONS");
    
    drawSettingsState.pageNum = draw_file_names(settings_options, 4, drawSettingsState.result.status, 0, 1, 1, 0, WiFi_options_icons);
    drawSettingsState.selectedFileData = return_select_label(settings_options, drawSettingsState.result.command, drawSettingsState.result.y, drawSettingsState.pageNum);

}
void draw_settings_selected_option(int selected_fileIndex){
    switch(selected_fileIndex){
        case 0:
            display_brightness_settings();
            break;
       
    }
}
void display_setings_option(){

    while(1){
        ESP.wdtDisable();
        u8g2.clearBuffer();
         drawSettingsState.result = draw_selecting_icon(1);
        if(drawSettingsState.result.command == BACK) break;
        
        if(drawSettingsState.selectedFileData.isSelected){
                draw_settings_selected_option(drawSettingsState.selectedFileData.fileIndex);
        }
        draw_setings_options();

        u8g2.sendBuffer();


        ESP.wdtEnable(WDTO_8S);


    }



}
















#endif // DRAW_SETTINGS_OPTIONS_H