#ifndef BIN_IMG_BROWSER
#define BIN_IMG_BROWSER

#include <ESP8266WiFi.h>
#include <UserInputs.h>
#include <ReadBinary.h>
#include <drawBinImage.h>
#include <drawBinVievOptions.h>
#include <FPSLimitter.h>
#include <VideoPlayer.h>

void browse_bin_image(char* directory) {
    
    int page = 1;  
    Draw_Image image = read_binary_image(directory, page);
    DrawChoise choise = {0,0};
    Choise_info select_info = {0,0};

    while(image.image_pages > 1 && !choise.drawImage && !choise.drawVideo){
        ESP.wdtDisable();
        choise = draw_select_viev_option(directory,image.image_pages);
        ESP.wdtEnable(WDTO_8S);
    }
    if(image.image_pages == 1)
        choise.drawImage = true;

    if(choise.drawImage){
        while(!select_info.exit){
            ESP.wdtDisable();
            if (select_info.next_page){ 
                image = read_binary_image(directory, page);
            }
            select_info = VievСhoise_image(page,image.image_pages);
            drawBin_image(image.image_buffer,0);
            ESP.wdtEnable(WDTO_8S);
            
        }
        yield();
        getParentDirectory(directory);
       // system_update_cpu_freq(80);

    }
    if(choise.drawVideo){
        FPSLimiter fpsLimit(15);
        while (!select_info.exit) {
            static bool open_player = false;
            ESP.wdtDisable();

            if(!fpsLimit.shouldRenderFrame()) continue;

            if(select_info.open_player)
                open_player = !open_player;

            if (select_info.next_page)
                image = read_binary_image(directory, page);
            


            select_info = VievChoise_video(page, image.image_pages);
            drawBin_image(image.image_buffer,open_player);
            fpsLimit.updateFPS();

            ESP.wdtEnable(WDTO_8S);
        }

        yield();
        getParentDirectory(directory);

    } 
    yield();
}








#endif