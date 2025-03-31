#ifndef DRAW_DEAUTH_WIFI
#define DRAW_DEAUTH_WIFI

#include <Arduino.h>
#include <DisplayConfig.h>
#include <WiFi Draw/draw_connect_toWiFi.h>


void draw_selected_death_SSID(char* selected_SSID, byte selected_ssid_index){
   
}

void display_select_death_ssid(){
    get_SSID_LIST();
    while(1){
        ESP.wdtDisable();
        u8g2.clearBuffer();
        draw_ssid_list_menu();
        drawSSidListState.result = draw_selecting_icon(1);
        if(drawSSidListState.result.command == BACK) break;

        if(drawSSidListState.result.command ==  UPDATE_SSIDS){
            draw_scanning_SSID();
            get_SSID_LIST();

        }
        if(drawSSidListState.selectedFileData.isSelected){
            Serial.print("Selected SSID:");
            Serial.println(drawSSidListState.selectedFileData.fileName);
            bool exist = check_SSID_existing(drawSSidListState.selectedFileData.fileName);
                

        }

        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);







    }



}












#endif