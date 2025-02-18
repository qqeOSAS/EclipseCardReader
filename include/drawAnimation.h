#ifndef DRAW_ANIM
#define DRAW_ANIM

#include <Arduino.h>
#include <DisplayConfig.h>
#include <Bitmaps_headers/Rotating_SD_gif_bitmap.h>

struct AnimationData {
    const uint8_t** frames;  // Масив вказівників на кадри (масив кадрів)
    int frames_count;
    byte width;
    byte height;
    byte x;
    byte y;
};

void draw_animation(AnimationData& anim_data, unsigned long* millis, unsigned long* timer, int change_frame_interval, int& current_frame) {
    if (*millis - *timer >= change_frame_interval) {
        *timer = *millis;
        current_frame++;
        if (current_frame >= anim_data.frames_count) 
            current_frame = 0; // Повертаємося до першого кадру
    }

    u8g2.drawXBMP(anim_data.x, anim_data.y, anim_data.width, anim_data.height, anim_data.frames[current_frame]);
}

void draw_sd_card_icon_animation(){
    static AnimationData spining_sd_Icon  = {Rotating_SD_gif_bitmap_25x35, 27, 25, 35, 4, 27};
    static int current_frame_1 = 0;
    static unsigned long timer_1 = 0;
    
    unsigned long cur_millis = millis();
    draw_animation(spining_sd_Icon, &cur_millis, &timer_1,50,current_frame_1);

}


#endif