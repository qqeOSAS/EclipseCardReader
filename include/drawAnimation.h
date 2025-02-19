#ifndef DRAW_ANIM
#define DRAW_ANIM

#include <Arduino.h>
#include <DisplayConfig.h>

struct AnimationData {
    const uint8_t** frames;  
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
            current_frame = 0; 
    }

    u8g2.drawXBMP(anim_data.x, anim_data.y, anim_data.width, anim_data.height, anim_data.frames[current_frame]);
}



#endif