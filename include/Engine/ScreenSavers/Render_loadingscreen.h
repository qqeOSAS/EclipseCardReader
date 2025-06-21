#ifndef screen_saver_h
#define screen_saver_h

#include <Arduino.h>
#include <DisplayConfig.h>
#include "Engine/engine.h"
#include <Bitmaps_headers/Bitmaps.h>
#include <drawAnimation.h>
#include <UserInputs.h>
#include <utils/ScreenShot.h>
#include <Engine/Doom_melt.h>

#define NUM_STARS 600
#define ANALOG_SEED_PIN A0

Vec3D* stars = nullptr;

// Виділення пам'яті
void allocateStars(int numStars) {
    if (stars) delete[] stars; // Якщо вже виділено — звільнити
    stars = new Vec3D[numStars];
}

// Звільнення пам'яті
void freeStars() {
    if (stars) {
        delete[] stars;
        stars = nullptr;
    }
}

// Ініціалізація однієї зірки
void resetStar(int i) {
    stars[i].x = random(-64, 64);
    stars[i].y = random(-32, 32);
    stars[i].z = random(16, 64); // avoid too close to center
}

// Ініціалізація всіх зірок
void initStarfield() {
    for (int i = 0; i < NUM_STARS; i++) {
        resetStar(i);
    }
}

// Проєкція 3D-точки у 2D-координати екрану
void projectStar(const Vec3D star, int& sx, int& sy) {
    sx = (int)(star.x * 64 / star.z) + 64;
    sy = (int)(star.y * 32 / star.z) + 32;
}

// Малювання однієї зірки
void drawStarShape(int x, int y) {
    u8g2.drawPixel(x, y); // центр
  
}

// Оновлення позиції зірки (рух вперед)
void updateStar(int i) {
    stars[i].z -= 0.6;
    if (stars[i].z <= 1) {
        resetStar(i);
    }
}

AcceleratedBitmapData Eclipse_logo1 = {
    .end_x = 5,
    .end_y = 0,
    .start_x = -65,
    .start_y = 5,
    .x_speed = 2,
    .y_speed = 2,
    .max_x_speed = 20,
    .max_y_speed = 0,
    .axis = 1,
    .x_acceleration = 2,
    .y_acceleration = 2,
    .accelerate_direction = true,
    .bitmap_width = 65,
    .bitmap_height = 15,
    .bitmap = epd_bitmap_Eclipse_logo_65x15
};

AcceleratedBitmapData cardreader_logo = {
    .end_x = 25,
    .end_y = 0,
    .start_x = -65,
    .start_y = 23,
    .x_speed = 2,
    .y_speed = 2,
    .max_x_speed = 25,
    .max_y_speed = 0,
    .axis = 1,
    .x_acceleration = 2,
    .y_acceleration = 2,
    .accelerate_direction = true,
    .bitmap_width = 60,
    .bitmap_height = 13,
    .bitmap = epd_bitmap_cardreaded_logo_60x13
};


AcceleratedTextData version_number = {
    .end_x = 0,
    .end_y = 35,
    .start_x = 90   ,
    .start_y = -30,
    .x_speed = 2,
    .y_speed = 2,
    .max_x_speed = 20,
    .max_y_speed = 15,
    .axis = 2,
    .x_acceleration = 2,
    .y_acceleration = 2,
    .accelerate_direction = true,
}; 
AcceleratedTextData by_qqeOSAS = {
    .end_x = 65,
    .end_y = 47,
    .start_x = -65   ,
    .start_y = 47,
    .x_speed = 2,
    .y_speed = 2,
    .max_x_speed = 20,
    .max_y_speed = 15,
    .axis = 1,
    .x_acceleration = 2,
    .y_acceleration = 2,
    .accelerate_direction = true,
};


void change_contrast(unsigned long current_time, bool animation1_started) {
    static unsigned long contrast_timer = 0;
    static int brightness = 0;
    if(current_time - contrast_timer >= 10 && !animation1_started) {
        contrast_timer = current_time;
        if(brightness < 255)
            brightness += 10;
        else
            brightness = 255; // Збільшуємо яскравість на 5

    }
    u8g2.setContrast(brightness);

}
// Малювання всього зоряного поля
void drawStarfield() {
    
    for (int i = 0; i < NUM_STARS; i++) {
        updateStar(i);
        if (stars[i].z <= 1) continue;

        int sx, sy;
        projectStar(stars[i], sx, sy);

        if (sx >= 0 && sx < 128 && sy >= 0 && sy < 64) {
            drawStarShape(sx, sy);
        }
    }

}
void draw_Eclipse_logos(){
    static unsigned long start_time = millis();
    static unsigned long animation1_start_time = start_time + 2000;
    static unsigned long animation2_start_time = animation1_start_time + 700;
    static unsigned long animation3_start_time = animation2_start_time + 500;
    static unsigned long animation4_start_time = animation3_start_time + 500; // Uncomment if you have a third animation
    static bool animation1_started = false;
    static bool animation2_started = false;
    static bool animation3_started = false;
    static bool animation4_started = false; // Uncomment if you have a third animation
    static unsigned long tmr_1 = 0;
    static unsigned long tmr_2 = 0;
    static unsigned long tmr_3 = 0;
    static unsigned long tmr_4 = 0; // Uncomment if you have a third animation
    long unsigned current_time = millis();

    if(current_time > animation1_start_time) {
        animation1_started = true;
    }
    if(current_time > animation2_start_time){
        animation2_started = true;
    }
    if(current_time > animation3_start_time){
       animation3_started = true; //animation3_started = true; // Uncomment if you have a third animation
    }
    if(current_time > animation4_start_time){
        animation4_started = true; // Uncomment if you have a third animation
    }
    
    change_contrast(current_time, animation1_started);
    draw_accelerated_bitmap(Eclipse_logo1, &current_time, &tmr_1, animation1_started);
    draw_accelerated_bitmap(cardreader_logo, &current_time, &tmr_2, animation2_started);
    draw_accelerated_text("V.1.1.0",version_number, &current_time, &tmr_4, animation4_started);
    draw_accelerated_text("by qqeOSAS",by_qqeOSAS, &current_time, &tmr_3, animation3_started);
    
    
}

void Eclipse_loading_screen() {
    randomSeed(analogRead(A0));
    allocateStars(NUM_STARS);
    initStarfield();
    
    unsigned long start_time = millis();
    unsigned long current_time = start_time;
    uint_8t_xbm_image eclipse_logo = {0,0, nullptr};

    while (1) {
        ESP.wdtDisable(); // 10 seconds loading screen
        u8g2.clearBuffer();
        current_time = millis();
        draw_Eclipse_logos();
        drawStarfield();
        u8g2.sendBuffer();
        int serial_cmd = serial_command();
        
        if (serial_cmd == BACK){
            char* screenshot_filepath = process_screenshot();
            if (screenshot_filepath != NULL) {
                eclipse_logo = extract_XBM_uint8_t(screenshot_filepath);
                free(screenshot_filepath); // Звільняємо пам'ять після використання
            }
            while(1){
                ESP.wdtDisable();
                u8g2.clearBuffer();
                //doom_melt(eclipse_logo.image_buffer,epd_bitmap_test_image);
                doom_melt(epd_bitmap_doom, epd_bitmap_test_image);
                ESP.wdtEnable(WDTO_8S);
            }
        }
        
        Serial.println("WDT enabled");
      
        Serial.println("freeStars OK");
        ESP.wdtEnable(WDTO_8S);
    }
    freeStars(); // Clean up memory after use
}


#endif