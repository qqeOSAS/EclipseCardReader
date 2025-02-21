#ifndef ICON_ANIMATIONS_H
#define ICON_ANIMATIONS_H

#include <Arduino.h>
#include <drawAnimation.h>
#include <Bitmaps_headers/Rotating_SD_gif_bitmap.h>
#include <Bitmaps_headers/WiFi_Icon_gif_bitmap.h>
#include <Bitmaps_headers/Setings_icon_animation_bitmap.h>




void draw_sd_card_icon_animation(bool draw_anim){
    static AnimationData spining_sd_Icon  = {Rotating_SD_gif_bitmap_25x35, 27, 25, 35, 4, 27};
    static int current_frame = 0;
    static unsigned long timer_1 = 0;
    
    unsigned long cur_millis = millis();
    if(!draw_anim)
        u8g2.drawXBMP(4,27,25,35,spining_sd_Icon.frames[0]);
    else
        draw_animation(spining_sd_Icon, &cur_millis, &timer_1,50,current_frame);


}
void draw_WiFi_icon_animation(bool draw_anim){
    static AnimationData WiFi_icon_anim = {WiFi_icon_animation_25x35, 21, 25, 35, 38, 23};
    static int current_frame = 0;
    static unsigned long timer_1 = 0;

    unsigned long cur_millis = millis();
    if(!draw_anim)
        u8g2.drawXBMP(38,23,25,35,WiFi_icon_anim.frames[0]);
    else
        draw_animation(WiFi_icon_anim, &cur_millis, &timer_1, 50, current_frame);
}
void draw_setings_icon_animation(bool draw_anim){
    static AnimationData Setings_icon_anim = {Setings_icon_animation_25X35, 31, 25, 35, 72, 27};
    static int current_frame = 0;
    static unsigned long timer_1 = 0;

    unsigned long cur_millis = millis();
    if(!draw_anim)
        u8g2.drawXBMP(72,27,25,35,Setings_icon_anim.frames[0]);
    else
        draw_animation(Setings_icon_anim,&cur_millis, &timer_1, 50, current_frame);

}











#endif