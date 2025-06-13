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

struct AcceleratedBitmapData {
    int end_x;
    int end_y;
    int start_x;
    int start_y;
    int x_speed = 0;
    int y_speed = 0;
    byte max_x_speed;
    byte max_y_speed;
    byte axis;
    int x_acceleration = 0;
    int y_acceleration = 0;
    bool accelerate_direction = true;
    // bitmap-specific fields
    byte bitmap_width;
    byte bitmap_height;
    const uint8_t* bitmap;
};

struct AcceleratedTextData {
    int end_x;
    int end_y;
    int start_x;
    int start_y;
    int x_speed = 0;
    int y_speed = 0;
    byte max_x_speed;
    byte max_y_speed;
    byte axis;
    int x_acceleration = 0;
    int y_acceleration = 0;
    bool accelerate_direction = true;
};

// --- Шаблонна функція ---
template<typename T>
void accelerate_by_axis(T& anim_data) {
    switch(anim_data.axis) {
        case 1: // X axis
            anim_data.x_speed += anim_data.x_acceleration;
            if (abs(anim_data.x_speed) > anim_data.max_x_speed)
                anim_data.x_speed = (anim_data.x_speed > 0 ? anim_data.max_x_speed : -anim_data.max_x_speed);

            if (anim_data.accelerate_direction) { // Вправо
                if (anim_data.start_x < anim_data.end_x)
                    anim_data.start_x += anim_data.x_speed;
                else
                    anim_data.start_x = anim_data.end_x;
            } else { // Вліво
                if (anim_data.start_x > anim_data.end_x)
                    anim_data.start_x -= anim_data.x_speed;
                else
                    anim_data.start_x = anim_data.end_x;
            }
            break;
        case 2: // Y axis
            anim_data.y_speed += anim_data.y_acceleration;
            if (abs(anim_data.y_speed) > anim_data.max_y_speed)
                anim_data.y_speed = (anim_data.y_speed > 0 ? anim_data.max_y_speed : -anim_data.max_y_speed);

            if (anim_data.accelerate_direction) { // Вниз
                if (anim_data.start_y < anim_data.end_y)
                    anim_data.start_y += anim_data.y_speed;
                else
                    anim_data.start_y = anim_data.end_y;
            } else { // Вгору
                if (anim_data.start_y > anim_data.end_y)
                    anim_data.start_y -= anim_data.y_speed;
                else
                    anim_data.start_y = anim_data.end_y;
            }
            break;
        case 3: // DUAL axis
            // Аналогічно для обох осей, якщо потрібно
            break;
    }
}
void draw_accelerated_bitmap(AcceleratedBitmapData& anim_data, unsigned long* millis, unsigned long* timer,bool draw_acceraled_bitmap_b) {
    if(!draw_acceraled_bitmap_b)
        return;

    if(*millis - *timer >=  20){
        *timer = *millis;
        accelerate_by_axis(anim_data);
    }
    u8g2.setBitmapMode(1);
    u8g2.drawXBMP(anim_data.start_x, anim_data.start_y, anim_data.bitmap_width, anim_data.bitmap_height, anim_data.bitmap);
}
void draw_accelerated_text(char* text,AcceleratedTextData& anim_data, unsigned long* millis, unsigned long* timer, bool draw_acceraled_text_b) {
    if(!draw_acceraled_text_b)
        return;

    if(*millis - *timer >=  20){
        *timer = *millis;
        accelerate_by_axis(anim_data);
    }
    u8g2.setFont(u8g2_font_NokiaSmallBold_tr);
    u8g2.setCursor(anim_data.start_x, anim_data.start_y);
    u8g2.print(text);
}



#endif