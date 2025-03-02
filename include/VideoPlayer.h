#ifndef VID_PLAY
#define  VID_PLAY
#include <DisplayConfig.h>
#include <Bitmaps_headers/Bitmaps.h>



void draw_player_menu(int y){
    u8g2.setColorIndex(0);
    u8g2.drawBox(0,y,128,14);
    u8g2.setColorIndex(1);
    u8g2.setBitmapMode(1);
    u8g2.drawXBMP(0,y,128,14,palyer_backgroung_image);
    u8g2.drawXBMP(58,y + 3,13,8, player_play_icon_bitmap);
    u8g2.drawXBMP(74,y + 3,13,8, player_stop_icon_bitmap);
    u8g2.drawXBMP(89,y + 3,13,8, move_frames_right_icon_bitmap);
    u8g2.drawXBMP(42,y + 3,13,8, move_frames_left_icon_bitmap);





}



#endif