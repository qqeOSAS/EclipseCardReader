#ifndef DRAW_SETTINGS_OPTIONS_H
#define DRAW_SETTINGS_OPTIONS_H

#include <Arduino.h>
#include <math.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <Bitmaps_headers/Bitmaps.h>
#include "draw_brightness_settings.h"

DrawOptionsState drawSettingsState;
char settings_options[][30] = {"Display Brightness", "NEW MENU", "System Settings", "About"};


void draw_setings_options(){
    u8g2.setColorIndex(1);
    draw_directory_info(" SETTINGS OPTIONS");
    
    drawSettingsState.pageNum = draw_file_names(settings_options, 4, drawSettingsState.result.status, 0, 1, 1, 0, WiFi_options_icons);
    drawSettingsState.selectedFileData = return_select_label(settings_options, drawSettingsState.result.command, drawSettingsState.result.y, drawSettingsState.pageNum);

}

// Простий приклад 16x16 битмапа для фокусу/рамки або іконки
const unsigned char icon[] PROGMEM = {
  0b00000000, 0b00000000,
  0b01111100, 0b00111110,
  0b01000010, 0b01000010,
  0b01000010, 0b01000010,
  0b01000010, 0b01000010,
  0b01111100, 0b00111110,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000
};

void draw_test_menu(){
    const int numItems = 6;
    static int selectedIndex = 0;
    float wheelPosition = static_cast<float>(selectedIndex);
    float targetPosition = wheelPosition;
    const char* const menuLabels[numItems] = {
        "Котейка",
        "Налаштування",
        "Інфо",
        "Медіа",
        "Батарея",
        "Профіль"
    };

    const int centerX = u8g2.getDisplayWidth() / 2;
    const int centerY = 110;
    const int radius = 75;
    const float angleStep = 0.35f;
    const int displayWidth = u8g2.getDisplayWidth();
    const int displayHeight = u8g2.getDisplayHeight();

    ESP.wdtDisable();
    unsigned long previousFrameTime = millis();

    while (true) {
        const int command = serial_command();
        if (command == BACK) {
            ESP.wdtEnable(WDTO_8S);
            return;
        }
        if (command == LIST_DOWN_MENU) {
            selectedIndex = (selectedIndex + 1) % numItems;
            targetPosition += 1.0f;
        } else if (command == LIST_UP_MENU) {
            selectedIndex = (selectedIndex + numItems - 1) % numItems;
            targetPosition -= 1.0f;
        }

        const unsigned long now = millis();
        const unsigned long frameTime = now - previousFrameTime;
        previousFrameTime = now;
        const float easing = 1.0f - expf(-static_cast<float>(frameTime) / 85.0f);
        wheelPosition += (targetPosition - wheelPosition) * easing;
        if (fabsf(targetPosition - wheelPosition) < 0.01f) {
            wheelPosition = targetPosition;
            if (targetPosition >= numItems) {
                targetPosition -= numItems;
                wheelPosition -= numItems;
            } else if (targetPosition < 0.0f) {
                targetPosition += numItems;
                wheelPosition += numItems;
            }
        }

        u8g2.clearBuffer();
        u8g2.setColorIndex(1);

        for (int i = 0; i < numItems; ++i) {
            float itemOffset = static_cast<float>(i) - wheelPosition;
            while (itemOffset > numItems / 2.0f) {
                itemOffset -= numItems;
            }
            while (itemOffset < -numItems / 2.0f) {
                itemOffset += numItems;
            }

            const float angle = -PI / 2.0f + itemOffset * angleStep;
            const int x = centerX + static_cast<int>(radius * cosf(angle) + 0.5f);
            const int y = centerY + static_cast<int>(radius * sinf(angle) + 0.5f);

            if (x < -12 || x > displayWidth + 12 || y < -12 || y > displayHeight + 12) {
                continue;
            }

            const float focus = 1.0f - fminf(fabsf(itemOffset), 1.0f);
            const int focusSize = 16 + static_cast<int>(8.0f * focus);
            const int focusRadius = 4 + static_cast<int>(2.0f * focus);
            if (focus > 0.01f) {
                u8g2.drawFrame(x - focusSize / 2, y - focusSize / 2, focusSize, focusSize);
                u8g2.drawDisc(x, y, focusRadius, U8G2_DRAW_ALL);
            } else {
                u8g2.drawCircle(x, y, 4);
            }
        }

        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        const char* selectedLabel = menuLabels[selectedIndex];
        const int labelWidth = u8g2.getUTF8Width(selectedLabel);
        u8g2.drawUTF8(centerX - labelWidth / 2, displayHeight - 1, selectedLabel);
        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
        delay(16);
        ESP.wdtDisable();
    }
}
void draw_settings_selected_option(int selected_fileIndex){
    switch(selected_fileIndex){
        case 0:
            display_brightness_settings();
            break;
        case 1:
            draw_test_menu();
            break;
       
    }
}
void display_setings_option(){

    while(1){
        ESP.wdtDisable();
        u8g2.clearBuffer();
         drawSettingsState.result = draw_selecting_icon(1);
        if(drawSettingsState.result.command == BACK) break;
        
        if(drawSettingsState.selectedFileData.isSelected){
                draw_settings_selected_option(drawSettingsState.selectedFileData.fileIndex);
                drawSettingsState.result.command = 0;
        }
        draw_setings_options();

        u8g2.sendBuffer();


        ESP.wdtEnable(WDTO_8S);


    }



}
















#endif // DRAW_SETTINGS_OPTIONS_H