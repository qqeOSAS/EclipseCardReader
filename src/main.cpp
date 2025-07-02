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
#include <WiFi/WiFi_auto_connect.h>

float angleX = 0, angleY = 0, angleZ = 0;

void setup() {
    Begin_display();
    draw_boot_one_line_message("[OK] SSD1306",800);
    draw_boot_3_line_message("Booting EclipseCardReader", "Version 1.1", "Initializing...", 1000);
    randomSeed(os_random());
    Serial.begin(115200);
    draw_boot_one_line_message("[INFO] init SSD1306",800);
    draw_boot_one_line_message("[INFO] init Controls",800);
    set_BTN_config();
    draw_boot_one_line_message("[INFO] init TimeClient",800);
    initTimeClient();
    draw_boot_one_line_message("[INFO] init SD card",800);

    SD_CARD_INITIALIZATION_STATUS = begin_SD(); // Ініціалізація NTP-клієнта
    if(SD_CARD_INITIALIZATION_STATUS){
        print_SD_info();
        draw_boot_one_line_message("[OK] SD card",800);
    }
    else
        draw_boot_one_line_message("[ERR] SD card",800);

    draw_boot_one_line_message("[INFO] init EEPROM",800);
    load_EEPROM_data();

    auto_connect_to_wifi();
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