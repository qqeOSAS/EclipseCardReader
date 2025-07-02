#ifndef BIN_VIEV_OPT
#define BIN_VIEV_OPT
#include <UserInputs.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#define OPEN_AS_VIDEO 40
#define OPEN_AS_IMAGE 50


struct DrawChoise{
    bool drawVideo;
    bool drawImage;
};
DrawChoise draw_select_viev_option(const char* directory,int images_num){
    DrawChoise choise = {0,0};

    u8g2.clearBuffer();
    //yield();
    u8g2.setColorIndex(1);
    draw_directory_info(directory);
    u8g2.setFont(u8g2_font_5x8_t_cyrillic);
    u8g2.setCursor(2,20);
    u8g2.print("Ваш файл має ");
    u8g2.print(images_num);
    u8g2.setCursor(2,30);
    u8g2.print("зображеня. Як відкрити?");
    u8g2.setCursor(2,50);
    u8g2.print("Відкрити як відео");
    u8g2.setCursor(2,60);
    u8g2.print("Відкрити як зображення");
    //yield();
    int command = serial_command();

    static int y = 50;

    switch (command) {
        case LIST_DOWN_MENU:
            y += 10;
            break;
        case LIST_UP_MENU:
            y -= 10;
            break;
        case SELECT:
            switch(y){
                case OPEN_AS_VIDEO:
                    choise.drawVideo = true;
                    break;
                case OPEN_AS_IMAGE:
                    choise.drawImage = true;
                    break;
            }
            break;
    }
    if (y < 35) 
        y = 50;
    else if (y > 55) 
        y = 40;
    


    u8g2.drawFrame(0,y,128,12);

    u8g2.sendBuffer();
    //yield();
    return choise;
}
struct Choise_info{
    bool next_page;
    bool exit;
    bool open_player;
    bool doom_melt_effect;
};
Choise_info VievСhoise_image(int& currentPage, int image_pages) {
    Choise_info info = {0,0};

    int command = serial_command(); 


    switch (command) {
        case LIST_DOWN_MENU:
            if (currentPage < image_pages) {
                currentPage++;
                info.next_page = true;
                Serial.println("Page increased");
            }
            break;
        case LIST_UP_MENU:
            currentPage--;
            info.next_page = true;
            if(currentPage <= 1)
                currentPage = 1;
            Serial.println("Page decreased");
            break;
        case BACK:
            info.exit = true;
            break;
        case OPEN_PLAYER:
            info.doom_melt_effect = true; // This could be used to trigger a special effect in the player
          break;
        }
    return info;
}
Choise_info VievChoise_video(int& currentPage, int image_pages){
    Choise_info  info = {0,0};
    int command = serial_command(); 
    
    switch(command){
        case BACK:
            info.exit = true;
            break;
        case OPEN_PLAYER:
            info.open_player = true;
            break;
    }

    unsigned long currentMillis = millis();
    if (currentPage <= image_pages) {
        currentPage++;
        info.next_page = true;
    }
    if (currentPage == image_pages) {
        currentPage = 1;
        info.next_page = true;
    }

    return info;
}






#endif