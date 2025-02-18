#ifndef DRAW_SCREEN_BROWSER
#define DRAW_SCREEN_BROWSER

#include <Arduino.h>
#include <DisplayConfig.h>
#include <Bitmaps.h>
#include <drawAnimation.h>



void draw_Clock(char* formated_time_str){
    u8g2.setColorIndex(0);
    u8g2.setFont(u8g2_font_fub14_tr);
    u8g2.setFontMode(1);
    u8g2.setCursor(3,18);
    u8g2.print("11:15PM"); 

}
void draw_main_screen_frame(){
    u8g2.setColorIndex(1);
    u8g2.setBitmapMode(1);
    u8g2.drawXBMP(0,0,128,64,main_screen_frames_bitmap_128x64);

}



void draw_main_screen(){
     
        u8g2.clearBuffer();
        draw_main_screen_frame();
        draw_Clock("11:15PM");
        
        u8g2.setColorIndex(1);
        draw_sd_card_icon_animation();

        
        u8g2.sendBuffer();
    
}













#endif