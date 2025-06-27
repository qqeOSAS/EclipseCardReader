#include <Arduino.h>
#include <SdCard_utils.h>
#include <drawSDFilesSystem.h>
#include <DisplayConfig.h>
#include <MainScreenBrowser.h>
#include <drawFileMenu.h>
#include <WiFi/Beacon_flood_attack.h>
#include <Engine/ScreenSavers/Render_loadingscreen.h>
#include <Apps/Timeclient/Time_client.h>
#include <EEPROM_manager/eeprom_utils.h>
//#include <WiFiManager.h> 

float angleX = 0, angleY = 0, angleZ = 0;

void setup() {
    int count;
    randomSeed(os_random());
    Serial.begin(115200);
    Begin_display();
    set_BTN_config();
    initTimeClient();
    bool begin_sd = begin_SD(); // Ініціалізація NTP-клієнта
    if(begin_sd){
        print_SD_info();
    }
    Serial.print("Поточна частота: ");
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println(" MHz");
    load_EEPROM_data();
    eeprom_print();
    system_update_cpu_freq(160);
    Eclipse_loading_screen();
    apply_display_EEPROM_settings();
  
    
}
screenshoot_path w = {NULL};
void loop() {
    //draw_file_properties("data.txt");
   // draw_directory();
    draw_main_screen(&w,0);
   
   //draw_fake_ssid_flooding();
   //run_flood_attack(false, 250, 0); // Запуск атаки з WPA2
   //handleUpload();
}