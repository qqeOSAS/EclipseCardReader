#include <Arduino.h>
#include <SdCard_utils.h>
#include <drawSDFilesSystem.h>
#include <DisplayConfig.h>
#include <MainScreenBrowser.h>
#include <drawFileMenu.h>
#include <WiFi/Beacon_flood_attack.h>
#include <3dEngine/engine.h>
#include <Apps/Timeclient/Time_client.h>
//#include <WiFiManager.h> 


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
    //init_upload_server();
   // generateDetailedCube(); // викликати один раз у setup()
   //createSphereMesh(sphereMesh, 3); // Створюємо сітку сфери
    //drawCube(0, 0, 0); // Малюємо куб
    //drawSphere(0, 0, 0, 2); // Малюємо сферу
    //drawDetailedCube(0, 0, 0); // Малюємо детальний куб
    //drawFakeSSIDFlooding(); // Малюємо фейкові SSID
    //}
    //drawFakeSSIDFlooding();
    //run_flood_attack(false, 250, 0); // Запуск атаки з WPA2
    //handleUpload();
    //mySphere = createSphereMesh(4); // або інша кількість сегментів
   // mySphere = createSphereMesh(2);
   // drawMesh(myShape, angleX, angleY, angleZ);

   // system_update_cpu_freq(160);
    
    
}
float angleX = 0, angleY = 0, angleZ = 0;

void loop() {
    //draw_file_properties("data.txt");

   // draw_directory();
    draw_main_screen();
   
   //draw_fake_ssid_flooding();
   //run_flood_attack(false, 250, 0); // Запуск атаки з WPA2
   //handleUpload();
}