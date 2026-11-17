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

const unsigned char menuCatIcon[] PROGMEM = {
     0x00, 0x00, 0x18, 0x18, 0x1E, 0x78, 0x7F, 0xFE,
     0xFF, 0xFF, 0xFE, 0x7F, 0xFE, 0x7F, 0x08, 0x10,
     0x08, 0x10, 0x80, 0x01, 0x3E, 0x7C, 0xFC, 0x3F,
     0xF8, 0x1F, 0xE0, 0x07, 0x00, 0x00, 0x00, 0x00
};

const unsigned char menuSettingsIcon[] PROGMEM = {
     0x00, 0x00, 0xC0, 0x03, 0xE0, 0x07, 0x38, 0x1C,
     0x1C, 0x38, 0x1E, 0x78, 0x0F, 0xF0, 0x3F, 0xFC,
     0xFC, 0x3F, 0x3F, 0xFC, 0x0F, 0xF0, 0x1E, 0x78,
     0x1C, 0x38, 0x38, 0x1C, 0xE0, 0x07, 0xC0, 0x03
};

const unsigned char menuInfoIcon[] PROGMEM = {
     0x00, 0x00, 0xC0, 0x03, 0xE0, 0x07, 0x30, 0x0C,
     0x18, 0x18, 0x0C, 0x30, 0x06, 0x60, 0x02, 0x40,
     0x82, 0x41, 0x82, 0x41, 0x02, 0x40, 0x02, 0x40,
     0x06, 0x60, 0x0C, 0x30, 0x18, 0x18, 0x00, 0x00
};

const unsigned char menuMediaIcon[] PROGMEM = {
     0x00, 0x00, 0x08, 0x00, 0x18, 0x00, 0x38, 0x00,
     0x78, 0x00, 0xF8, 0x00, 0xF8, 0x01, 0xF8, 0x03,
     0xF8, 0x03, 0xF8, 0x01, 0xF8, 0x00, 0x78, 0x00,
     0x38, 0x00, 0x18, 0x00, 0x08, 0x00, 0x00, 0x00
};

const unsigned char menuBatteryIcon[] PROGMEM = {
     0x00, 0x00, 0xF0, 0x0F, 0xF8, 0x1F, 0x04, 0x20,
     0x04, 0x20, 0xE4, 0x23, 0xC4, 0x21, 0x84, 0x21,
     0x04, 0x21, 0x1C, 0x21, 0x38, 0x21, 0x04, 0x20,
     0x04, 0x20, 0xF8, 0x1F, 0xF0, 0x0F, 0x00, 0x00
};

const unsigned char menuProfileIcon[] PROGMEM = {
     0x00, 0x00, 0x00, 0x00, 0xC0, 0x03, 0xE0, 0x07,
     0xE0, 0x07, 0xC0, 0x03, 0xF0, 0x0F, 0xF8, 0x1F,
     0xFC, 0x3F, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0x00, 0x00
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
    const unsigned char* const menuIcons[numItems] = {
        menuCatIcon,
        menuSettingsIcon,
        menuInfoIcon,
        menuMediaIcon,
        menuBatteryIcon,
        menuProfileIcon
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
            u8g2.drawXBMP(x - 8, y - 8, 16, 16, menuIcons[i]);
            if (focus > 0.01f) {
                u8g2.drawFrame(x - focusSize / 2, y - focusSize / 2, focusSize, focusSize);
            }
            if (i == 1) {
                u8g2.setColorIndex(0);
                u8g2.drawDisc(x, y, 3, U8G2_DRAW_ALL);
                u8g2.setColorIndex(1);
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