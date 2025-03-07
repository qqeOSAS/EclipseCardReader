#ifndef RENAME_FILE
#define RENAME_FILE

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>

void draw_rename_file(char* filename){

    u8g2.setColorIndex(1);
    u8g2.drawBox(0, 0, 128, 10);
    u8g2.setColorIndex(0);
    u8g2.setFontMode(1);
    u8g2.setFont(u8g2_font_6x13_t_cyrillic);
    u8g2.setCursor(0, 9);
    u8g2.print(filename);
    //u8g2.drawRFrame(3, 42, 122, 12, 4);
   // u8g2.setFont(u8g2_font_NokiaSmallBold_tr);
   //u8g2.setCursor(15, 51);
   // u8g2.print("Delete: ");
   // u8g2.setFont(u8g2_font_5x8_t_cyrillic);
   // u8g2.print(filename);
   // u8g2.setFont(u8g2_font_NokiaSmallBold_tr);
   // u8g2.setCursor(15, 62);
   // u8g2.print("Cancel && Exit)");
   // u8g2.sendBuffer();
}





#endif