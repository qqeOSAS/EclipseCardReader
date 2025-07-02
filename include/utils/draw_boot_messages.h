#ifndef Draw_Boot_Messages_H
#define Draw_Boot_Messages_H

#include  <DisplayConfig.h>

void draw_boot_one_line_message(const char* message,int delay_time) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setCursor(0, 10);
    u8g2.print(message);
    u8g2.sendBuffer();
    delay(delay_time);
}
void draw_boot_3_line_message(const char* message1,const char* message2,const char* message3, int delay_time) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_5x7_mf);
    u8g2.setCursor(0, 10);
    u8g2.print(message1);
    u8g2.setCursor(0, 20);
    u8g2.print(message2);
    u8g2.setCursor(0, 30);
    u8g2.print(message3);
    u8g2.sendBuffer();
    delay(delay_time);
}





#endif