
#include <Arduino.h>
#include <SdCard_utils.h>
#include <drawFilesystem.h>
#include <DisplayConfig.h>
#include <MainScreenBrowser.h>
 


void setup() {
    int count;
    Serial.begin(115200);
    Begin_display();
    set_BTN_config();
    if(begin_SD()){
        print_SD_info();
      
    }
    Serial.print("Поточна частота: ");
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println(" MHz");
   //   if (myFile.open("data.txt", FILE_WRITE)) {
   // myFile.println("TEST WRITE DAATA.");
   // myFile.println("WRITED DATA: 12345");
  //  myFile.close(); // Закриваємо файл
 // } else {
 //   Serial.println("Не вдалося відкрити файл для запису.");
 // }

  // Читання з файлу

    


}

void loop() {

   // draw_directory();
   draw_main_screen();
    
}
