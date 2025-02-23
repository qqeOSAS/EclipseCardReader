#ifndef WIFI_OPTIONS
#define WIFI_OPTIONS


#include <Arduino.h>
#include <UserInputs.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>

struct DrawWiFiOptionsState {
    int step = 0;         
    int OptionCount = 0;   
    int pageNum = 0;      
    bool reset_page = false;
    CommandData result;
    SelectedFile selectedFileData;
};

DrawWiFiOptionsState drawWiFiState;


char wifi_options[][30] = {"Connect to WiFi", "Disconnect from WiFi", "ESP_Now","WiFi Jammer","WiFi_deauther","newoption","SDDSd"};





void draw_wifi_options(){
    u8g2.clearBuffer();

    u8g2.setColorIndex(1);
    drawWiFiState.result = draw_selecting_icon(1);
    drawWiFiState.pageNum = draw_file_names(wifi_options, 7, drawWiFiState.result.status,0);
    drawWiFiState.selectedFileData = return_select_label(wifi_options, drawWiFiState.result.command, drawWiFiState.result.y, drawWiFiState.pageNum);



    

    u8g2.sendBuffer();
}
void displayWiFiOptions(){
    while(1){
        ESP.wdtDisable();

        draw_wifi_options();
        ESP.wdtEnable(WDTO_8S);
    }
}






#endif