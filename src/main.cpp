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
#define NUM_STARS 100
#define ANALOG_SEED_PIN A0

struct Star {
  float x, y, z;
};

Star stars[NUM_STARS];

void resetStar(int i) {
  stars[i].x = random(-64, 64);
  stars[i].y = random(-32, 32);
  stars[i].z = random(16, 64); // avoid too close to center
}void drawStarShape(int x, int y) {
  u8g2.drawLine(x-1, y, x+1, y);   // горизонтальна
  u8g2.drawLine(x, y-1, x, y+1);   // вертикальна
}


void drawStarfield() {
  u8g2.clearBuffer();

  for (int i = 0; i < NUM_STARS; i++) {
    // Move star closer (simulate depth)
    stars[i].z -= 0.8;
    if (stars[i].z <= 1) {
      resetStar(i);
      continue;
    }

    // Project 3D to 2D
    int sx = (int)(stars[i].x * 64 / stars[i].z) + 64;
    int sy = (int)(stars[i].y * 32 / stars[i].z) + 32;

    // Draw if within screen bounds
    if (sx >= 0 && sx < 128 && sy >= 0 && sy < 64) {
        // Draw star shape
        drawStarShape(sx, sy);
    }
  }

  u8g2.sendBuffer();
}


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
    //    analogReadResolution(10); // For ESP8266 10-bit (not available on ESP8266)
  randomSeed(analogRead(ANALOG_SEED_PIN));
  u8g2.begin();

  for (int i = 0; i < NUM_STARS; i++) {
    resetStar(i);
  }
 
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
    drawStarfield();
   // draw_directory();
    //draw_main_screen();
   
   //draw_fake_ssid_flooding();
   //run_flood_attack(false, 250, 0); // Запуск атаки з WPA2
   //handleUpload();
}