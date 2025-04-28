#ifndef DRAW_SCREEN_BROWSER
#define DRAW_SCREEN_BROWSER

#include <Arduino.h>
#include <DisplayConfig.h>
#include <Bitmaps_headers/Bitmaps.h>
#include <Icon_animations.h>
#include <UserInputs.h>
#include <User_Interface/main_screen_user_inputs.h>
#include <drawSDFilesSystem.h>
#include <drawWifi_options.h>
#include <WiFi/Wifi_config.h>
#include <Apps/Timeclient/Time_client.h>
#include <display_interface_utils.h>


void draw_active_bar(int hours, int minutes){
    draw_wifi_strengh_icon();
    u8g2.setBitmapMode(1);

    u8g2.setColorIndex(0);
    u8g2.setFont(u8g2_font_fub14_tr);
    u8g2.setFontMode(1);
    u8g2.setCursor(5,19);
    u8g2.printf("%02d:%02d", hours, minutes);
    u8g2.setColorIndex(1);


}
void draw_main_screen_frame(){
    u8g2.setColorIndex(1);
    u8g2.setBitmapMode(1);
    u8g2.drawXBMP(0,0,128,64,main_screen_frames_bitmap_128x64);

}

void draw_main_screen_selecting_icon(int select_icon_num){
    switch(select_icon_num){
        case 0:
            u8g2.drawRFrame(1,27,30,37,5); break;
        case 1:
            u8g2.drawRFrame(35,27,30,37,5); break;
        case 2:
            u8g2.drawRFrame(69,27,30,37,5); break;
    }

}



void draw_main_screen(){
    ESP.wdtDisable();
        int command = serial_command();
        Selected_Icon_Info icon_info = get_select_icon(command);

        if(WIFI_CONNECTION_STATUS)
            getTime(); // Отримуємо час з NTP-сервера
        Serial.printf("%d:%d date:%d\n", time_data.hours, time_data.minutes, time_data.day);

        conection_checker();
        Serial.printf("WIFI_CONNECTION_STATUS: %d\n", WIFI_CONNECTION_STATUS);
        
        u8g2.clearBuffer();
        draw_main_screen_frame();
        draw_active_bar(time_data.hours, time_data.minutes);
        draw_sd_card_icon_animation(icon_info.draw_anim1);
        draw_WiFi_icon_animation(icon_info.draw_anim2);
        draw_setings_icon_animation(icon_info.draw_anim3);
        draw_main_screen_selecting_icon(icon_info.select_icon_num);

        if(icon_info.selected_b){
            switch(icon_info.select_icon_num){
                case 0:
                    displaySDFileSystem();  break;
                case 1:
                    displayWiFiOptions(); break;
            }
        }


        
        u8g2.sendBuffer();
    ESP.wdtEnable(WDTO_8S);
}













#endif