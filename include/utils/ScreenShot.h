#ifndef screen_shot_h
#define screen_shot_h

#include <Arduino.h>
#include <DisplayConfig.h>
#include <SdCard_utils.h>



char* process_screenshot() {
    if (!begin_SD()) {
        Serial.println("SD card initialization failed!");
        return NULL;
    }

    // Формуємо унікальне ім'я файлу
    char filename[30];
    sprintf(filename, "screenshot_%lu", millis());

    // Зберігаємо скріншот
    save_xbm_screenshot("/Screenshots", filename);

    // Формуємо повний шлях до файлу
    char* full_filepath = (char*)malloc(strlen("/Screenshots/") + strlen(filename) + 5); // +5 для ".xbm" і '\0'
    if (!full_filepath) return NULL;
    sprintf(full_filepath, "/Screenshots/%s.xbm", filename);

    Serial.print("Screenshot saved to: ");
    Serial.println(full_filepath);

    return full_filepath; // Пам'ять під цей рядок треба буде звільнити після використання!
}








#endif // screen_shot_h