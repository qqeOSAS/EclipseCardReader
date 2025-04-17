#include <Arduino.h>
#include <SdCard_utils.h>
#include <drawSDFilesSystem.h>
#include <DisplayConfig.h>
#include <MainScreenBrowser.h>
#include <drawFileMenu.h>
#include <WiFi/Beacon_flood_attack.h>
//#include <WiFiManager.h> 

void setup() {
    int count;
    randomSeed(os_random());
    Serial.begin(115200);
    Begin_display();
    set_BTN_config();
    if(begin_SD()){
        print_SD_info();
      
    }
    Serial.print("Поточна частота: ");
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println(" MHz");
    //init_flood_attack(false); // Ініціалізація атаки з WPA2
    //while(1){
   //     ESP.wdtDisable();
   //     run_flood_attack(false, 250); // Запуск атаки з WPA2
   //     ESP.wdtEnable(WDTO_8S);
   // }
   //   if (myFile.open("data.txt", FILE_WRITE)) {
   // myFile.println("TEST WRITE DAATA.");
   // myFile.println("WRITED DATA: 12345");
  //  myFile.close(); // Закриваємо файл
 // } else {
 //   Serial.println("Не вдалося відкрити файл для запису.");
    //system_update_cpu_freq(160);
    //init_flood_attack(0);
}

void loop() {
    //draw_file_properties("data.txt");

   // draw_directory();
    draw_main_screen();
   //draw_fake_ssid_flooding();
   //run_flood_attack(false, 250, 0); // Запуск атаки з WPA2
}