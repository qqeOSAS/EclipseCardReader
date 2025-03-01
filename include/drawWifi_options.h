#ifndef WIFI_OPTIONS
#define WIFI_OPTIONS


#include <Arduino.h>
#include <UserInputs.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <SdCard_utils.h>



DrawOptionsState drawWiFiState;


char wifi_options[][30] = {"Connect to WiFi", "Disconnect from WiFi", "ESP_Now", "WiFi Jammer", "WiFi_deauther", "newoption", "SDDSd"};

void draw_wifi_selected_option(int fileIndex){
    switch(fileIndex){
        case 0:
            Serial.print("SELECTED: ");
            Serial.println("Connect to WiFi");
            break;
        case 1:
            Serial.print("SELECTED: ");
            Serial.println("Disconnect from WiFi");
            break;
        case 2:
            Serial.print("SELECTED: ");
            Serial.println("ESP_Now");
            break;
        case 3:
            Serial.print("SELECTED: ");
            Serial.println("WiFi Jammer");
            break;
        case 4:
            Serial.print("SELECTED: ");
            Serial.println("WiFi_deauther");
            break;
        case 5:
            Serial.print("SELECTED: ");
            Serial.println("newoption");
            break;
        case 6:
            Serial.print("SELECTED: ");
            Serial.println("SDDSd");
            break;
    }
}


void draw_wifi_options(){

    u8g2.setColorIndex(1);
    draw_directory_info(" WIFI OPTIONS");
    drawWiFiState.pageNum = draw_file_names(wifi_options, 7, drawWiFiState.result.status,0);
    drawWiFiState.selectedFileData = return_select_label(wifi_options, drawWiFiState.result.command, drawWiFiState.result.y, drawWiFiState.pageNum);

    if(drawWiFiState.selectedFileData.isSelected){
        draw_wifi_selected_option(drawWiFiState.selectedFileData.fileIndex);
    }
}


void displayWiFiOptions(){
    while(1){
        static unsigned long timer_1 = 0;
        unsigned long currentMillis = millis();
        
        ESP.wdtDisable();

        if (currentMillis - timer_1 >= 5) {
            u8g2.clearBuffer();
            drawWiFiState.result = draw_selecting_icon(1);

            if(drawWiFiState.result.command == BACK) break;
            
            draw_wifi_options();
            timer_1 = currentMillis;
            u8g2.sendBuffer();
        }
        ESP.wdtEnable(WDTO_8S);
    }
}






#endif