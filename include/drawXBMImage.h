#ifndef DRAW_XBM
#define DRAW_XBM

#include <DisplayConfig.h>
//#include <SDCard.h>

void drawXBM_image(int widht,int height,uint8_t* image_buffer);


void drawXBM_image(int widht,int height,uint8_t* image_buffer){
    u8g2.setColorIndex(1);
    u8g2.clearBuffer();
    u8g2.drawXBM(0,0,widht,height,image_buffer);


    u8g2.sendBuffer();

}


#endif