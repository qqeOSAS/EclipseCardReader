// This file contains a function for displaying XBM (X Bitmap) images on the screen. 
// !!!!!!!Max image resulution 128x64.!!!!!!
// XBM images are typically used for simple monochrome bitmap graphics.
// You can prepare image here   https://www.online-utility.org/image/convert/to/XBM


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