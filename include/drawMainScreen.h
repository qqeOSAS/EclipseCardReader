#ifndef DRAW_SCREEN_BROWSER
#define DRAW_SCREEN_BROWSER

#include <Arduino.h>
#include <DisplayConfig.h>
#include <Bitmaps.h>
#include <Icon_animations.h>
#include <UserInputs.h>
#include <User_Interface/main_screen_user_inputs.h>
#include <drawSDFilesSystem.h>
#include <drawWifi_options.h>



void draw_Clock(char* formated_time_str){
    u8g2.setColorIndex(0);
    u8g2.setFont(u8g2_font_fub14_tr);
    u8g2.setFontMode(1);
    u8g2.setCursor(3,18);
    u8g2.print("11:15PM");
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
        int command = serial_command();
        Selected_Icon_Info icon_info = get_select_icon(command);


        u8g2.clearBuffer();
        draw_main_screen_frame();
        draw_Clock("11:15PM");
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
    
}













#endif