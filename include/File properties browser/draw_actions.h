#ifndef DRAW_ACTIONS
#define DRAW_ACTIONS

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>

DrawOptionsState PropertiesActionsState;

char Actions_options[][30] = {"Delete file", "Hide file", "Make read only", "Rename"};

void draw_properties_actions_selected_option(int fileIndex){
    switch(fileIndex){
        case 0:
            Serial.print("SELECTED: ");
            Serial.println("Delete file");
            break;
        case 1:
            Serial.print("SELECTED: ");
            Serial.println("Hide file");
            break;
        case 2:
            Serial.print("SELECTED: ");
            Serial.println("Make read only");
            break;
        case 3:
            Serial.print("SELECTED: ");
            Serial.println("Rename");
            break;
    }
}

void draw_properties_actions(){
    u8g2.setColorIndex(1);
    draw_directory_info("File properties/Actions");
    PropertiesActionsState.pageNum = draw_file_names(Actions_options, 4, PropertiesActionsState.result.status, 0);
    PropertiesActionsState.selectedFileData = return_select_label(Actions_options, PropertiesActionsState.result.command, PropertiesActionsState.result.y, PropertiesActionsState.pageNum);

    if(PropertiesActionsState.selectedFileData.isSelected){
        draw_properties_actions_selected_option(PropertiesActionsState.selectedFileData.fileIndex);
    }
}

void display_properties_actions(){
    static unsigned long timer_1 = 0;
    while(1){
        ESP.wdtDisable();
        unsigned long currentMillis = millis();

        if (currentMillis - timer_1 >= 5) {
            u8g2.clearBuffer();
            PropertiesActionsState.result = draw_selecting_icon(1);

            if(PropertiesActionsState.result.command == BACK) break;
            
            draw_properties_actions();
            timer_1 = currentMillis;
            u8g2.sendBuffer();
        }
        ESP.wdtEnable(WDTO_8S);
    }
}





#endif