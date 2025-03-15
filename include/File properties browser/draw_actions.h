#ifndef DRAW_ACTIONS
#define DRAW_ACTIONS

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <File properties browser/draw_edit_attributes.h>
#include <File properties browser/draw_delete_file.h>
#include <BinImageBrowser.h>

DrawOptionsState PropertiesActionsState;

char Actions_options[][30] = {"Delete file", "Edit attributes", "Rename","Open as bin image"};


void draw_properties_actions(){
    u8g2.setColorIndex(1);
    draw_directory_info("File properties/Actions");
    PropertiesActionsState.pageNum = draw_file_names(Actions_options, 4, PropertiesActionsState.result.status,PropertiesActionsState.reset_page,1,1,0,file_actions_icons);
    PropertiesActionsState.selectedFileData = return_select_label(Actions_options, PropertiesActionsState.result.command, PropertiesActionsState.result.y, PropertiesActionsState.pageNum);
}

void display_properties_actions(FileProperties* file_properties,char* file_name){
    static unsigned long timer_1 = 0;
    PropertiesActionsState.reset_page = true;
    bool exit = false;
    while(1){
        ESP.wdtDisable();
        unsigned long currentMillis = millis();

        if (currentMillis - timer_1 >= 5) {
            u8g2.clearBuffer();
            PropertiesActionsState.result = draw_selecting_icon(1);

            if(PropertiesActionsState.result.command == BACK) break;

            if(PropertiesActionsState.selectedFileData.isSelected){
                
                switch(PropertiesActionsState.selectedFileData.fileIndex){
                    case 0:
                        Display_delete_file(file_name);
                        exit = true;
                        PropertiesActionsState = {0,0,0,0,0,0};
                        break;
                    case 1:
                        Display_edit_attributes(file_properties,file_name);
                        exit = true;
                        PropertiesActionsState = {0,0,0,0,0,0};
                        break;
                    case 2:
                        //rename file
                        
                        break;
                    case 3:
                        browse_bin_image(file_name);
                        exit = true;
                        PropertiesActionsState = {0,0,0,0,0,0};
                        break;


                }
            }
            if (exit) break;
            
            draw_properties_actions();
            PropertiesActionsState.reset_page = false;

            timer_1 = currentMillis;
            u8g2.sendBuffer();
        }
        ESP.wdtEnable(WDTO_8S);
    }
}





#endif