#ifndef DRAW_BIN
#define DRAW_BIN

#include <DisplayConfig.h>
#include <VideoPlayer.h>

void drawBin_image(uint8_t* image_buffer,bool draw_player){
    unsigned long curerentMillis = millis();
    static unsigned long timer_1 = 0;
    u8g2.setColorIndex(1);
    u8g2.clearBuffer();
    u8g2.drawXBM(0,0,128,64,image_buffer);

    static int y = 70;
    if(draw_player){
        if( y > 50 &&curerentMillis - timer_1 >= 2){
            y -= 2;
            timer_1 = curerentMillis;
        }
        draw_player_menu(y);
    }
    else{
        y = 70;
    }



    u8g2.sendBuffer();

}




#endif