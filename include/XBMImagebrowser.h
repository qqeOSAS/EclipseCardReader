#ifndef XBM_BROWSER
#define XBM_BROWSER

#include <UserInputs.h>
#include <drawXBMImage.h>
#include <ReadXBM.h>



void browse_XBM_image(char* directory);


void browse_XBM_image(char* directory){
    system_update_cpu_freq(160);
    static unsigned long timer_1 = 0;
    unsigned long currentMillis = millis();
    Draw_Image image = read_XBM_image(directory);


    while(serial_command() != BACK){
        currentMillis = millis();
        if(currentMillis - timer_1 >= 50){
            drawXBM_image(image.width,image.height,image.image_buffer);
            timer_1 = currentMillis;
        }
        yield();
    }
    getParentDirectory(directory);
    system_update_cpu_freq(80);

    




}



#endif