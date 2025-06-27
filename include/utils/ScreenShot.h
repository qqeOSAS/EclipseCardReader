#ifndef screen_shot_h
#define screen_shot_h

#include <Arduino.h>
#include <DisplayConfig.h>
#include <SdCard_utils.h>

struct screenshoot_path {
    char* full_filepath;
};

screenshoot_path process_screenshot() {
    screenshoot_path result = {NULL};
    if (!begin_SD()) {
        Serial.println("SD card initialization failed!");
        return result;
    }

    // Формуємо унікальне ім'я файлу
    char* filename = (char*)malloc(30);
    sprintf(filename, "screenshot_%lu", millis());

    // Зберігаємо скріншот
    save_xbm_screenshot("/Screenshots", filename);

    // Формуємо повний шлях до файлу
    size_t path_len = strlen("/Screenshots/") + strlen(filename) + 5; // ".xbm" + '\0'
    result.full_filepath = (char*)malloc(path_len);
    if (!result.full_filepath) {
        Serial.println("Memory allocation failed!");
        return result;
    }

    sprintf(result.full_filepath, "/Screenshots/%s.xbm", filename);

    Serial.print("Screenshot saved to: ");
    Serial.println(result.full_filepath);
    free(filename);

    return result; // не забудь звільнити result.full_filepath вручну пізніше!
}








#endif // screen_shot_h