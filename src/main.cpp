
#include <Arduino.h>
#include <SdCard_utils.h>
#include <drawSDFilesSystem.h>
#include <DisplayConfig.h>
#include <MainScreenBrowser.h>
#include <drawFileMenu.h>
 


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

  draw_main_screen();

    //Display_delete_file("/Folder1/Текстові файли/історії/myfile.txt");
}

void loop() {
    //draw_file_properties("data.txt");

   // draw_directory();
   draw_main_screen();
    
}
