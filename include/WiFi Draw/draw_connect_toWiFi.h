#ifndef DRAW_CONNECT_TO_WIFI
#define DRAW_CONNECT_TO_WIFI 

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <WiFi/connect_to_WiFi.h>

DrawOptionsState drawSSidListState;

void draw_ssid_list_menu(){
  
    u8g2.setBitmapMode(1);
    u8g2.setColorIndex(1);
    draw_directory_info("SSID List");
    drawSSidListState.pageNum = draw_file_names(ssid_list_info.SSID_LIST, ssid_list_info.ssid_to_store, drawSSidListState.result.status,0);
    drawSSidListState.selectedFileData = return_select_label(ssid_list_info.SSID_LIST, drawSSidListState.result.command, drawSSidListState.result.y, drawSSidListState.pageNum);

}





void display_SSID_list(){
    unsigned long timer_1 = 0;
    get_SSID_LIST();
    while(1){
        unsigned long currentMillis = millis();


        ESP.wdtDisable();
        u8g2.clearBuffer();
        draw_ssid_list_menu();
        drawSSidListState.result = draw_selecting_icon(1);

        if(drawSSidListState.result.command == BACK) break;

        if(drawSSidListState.result.command ==  UPDATE_SSIDS){
            Serial.print("START TIME: ");
            Serial.println(millis());
            get_SSID_LIST();
            Serial.print("End TIME: ");
            Serial.println(millis());

        }

        u8g2.sendBuffer();





        ESP.wdtEnable(WDTO_8S);
    }
}
#endif