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

void drw_properties_actions(){
    u8g2.clearBuffer();
    u8g2.setColorIndex(1);
    draw_directory_info("File properties/Actions");
    PropertiesActionsState.result = draw_selecting_icon(1);
    PropertiesActionsState.pageNum = draw_file_names(Actions_options, 4, PropertiesActionsState.result.status, 0);
    PropertiesActionsState.selectedFileData = return_select_label(Actions_options, PropertiesActionsState.result.command, PropertiesActionsState.result.y, PropertiesActionsState.pageNum);

    if(PropertiesActionsState.selectedFileData.isSelected){
        draw_properties_actions_selected_option(PropertiesActionsState.selectedFileData.fileIndex);
    }
    u8g2.sendBuffer();
}
void draw_properties_actions(){
    static unsigned long timer_1 = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - timer_1 >= 5) { 
            drw_properties_actions();
            timer_1 = currentMillis;
        }
    yield(); 

}
void display_properties_actions(){
    while(1){
        listDown_btn.tick();
        if(listDown_btn.isHold())
            break;
        ESP.wdtDisable();
        draw_properties_actions();
        ESP.wdtEnable(WDTO_8S);
    }
}





#endif