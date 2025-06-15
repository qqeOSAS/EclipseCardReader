#ifndef screen_shot_h
#define screen_shot_h

#include <Arduino.h>
#include <DisplayConfig.h>
#include <SdCard_utils.h>


void save_screenshot_to_file( char* filename, uint8_t* buffer, size_t buffer_size) {
    begin_SD();
    SdFile file;
    create_directory("/Screenshots");
    create_bin_file("/Screenshots", filename, buffer, buffer_size);
}
void process_screenshot() {
    if(!begin_SD()) {
        Serial.println("SD card initialization failed!");
        return;
    }
    char* filename = (char*)malloc(30); // Allocate memory for the filename
    sprintf(filename, "screenshot_%4lu", millis()); // Create a unique filename based on current time
    save_xbm_screenshot("/Screenshots", filename);
    free(filename); // Free the filename memory
}








#endif // screen_shot_h