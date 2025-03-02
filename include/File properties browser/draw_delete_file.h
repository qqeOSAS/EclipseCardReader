#ifndef DRAW_DELETE_FILE
#define DRAW_DELETE_FILE    

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>

struct user_choice{
    bool is_selected = false;
    byte selected_option = 0;   
};
#define DELETE 0
#define CANCEL 1

user_choice draw_choice(int command,char* filename){
    user_choice user_choice = {false, 0};
    static int8 selected_icon = 0;

    switch (command) {
        case SELECT:
            user_choice.is_selected = true;
            user_choice.selected_option = selected_icon;
            break;
        case LIST_DOWN_MENU:
            selected_icon++;
            if (selected_icon > 1) selected_icon = 0;break;
        case LIST_UP_MENU:
            selected_icon--;
            if (selected_icon < 0) selected_icon = 1;break;
    }
    u8g2.setColorIndex(1);
    u8g2.drawRBox(0, 40, 128, 24,5);
    u8g2.setColorIndex(0);

    switch (selected_icon) {
        case 0:
            u8g2.drawRFrame(3, 42, 122, 12, 4); break;
        case 1:
            u8g2.drawRFrame(3, 52, 122, 12, 4); break;
    }
    u8g2.setFont(u8g2_font_NokiaSmallBold_tr);
    u8g2.setCursor(15, 62);
    u8g2.print("Cancel && Exit)");
    u8g2.setFontMode(1);
    u8g2.setCursor(10, 51);
    u8g2.print("Delete: ");
    u8g2.setFont(u8g2_font_5x8_t_cyrillic);
    u8g2.print(filename);

    return user_choice;
}
void draw_succesfull_delete(char* filename){
    unsigned long start_time = millis();
    unsigned long end_time = start_time + 2000;

    while(start_time < end_time){
        ESP.wdtDisable();
        u8g2.clearBuffer();
        draw_directory_info("File properties/Actions/Delete file");
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setCursor(5, 20); u8g2.print(filename);
        u8g2.setFont(u8g2_font_nokiafc22_tr);
        u8g2.setCursor(5, 30); u8g2.print("Successfully removed");


        



        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
        start_time = millis();
    }


}

void draw_delete_file(char* file_name){
    u8g2.setColorIndex(1);
    draw_directory_info("File properties/Actions/Delete file");
    u8g2.setFont(u8g2_font_nokiafc22_tr);
    u8g2.setCursor(5, 20); u8g2.print("Really want to remove:");
    u8g2.setFont(u8g2_font_5x8_t_cyrillic);
    u8g2.setCursor(5, 30); u8g2.print(file_name);

    u8g2.sendBuffer();
}
void Display_delete_file(char* file_name){
    static unsigned long timer_1 = 0;
    user_choice user_choice = {false, 0};
    while(1){
        Serial.println(file_name);
        ESP.wdtDisable();
        unsigned long currentMillis = millis();
        int command = serial_command();

        if (currentMillis - timer_1 >= 5) {
            u8g2.clearBuffer();
            user_choice = draw_choice(command,file_name);
            draw_delete_file(file_name);
            if(user_choice.is_selected){

                if(user_choice.selected_option == DELETE){
                    if(delete_sd_file(file_name))
                        draw_succesfull_delete(file_name);
                    break;
                }
                if(user_choice.selected_option == 1) break;
            }
            u8g2.sendBuffer();
            timer_1 = currentMillis;
        }
        ESP.wdtEnable(WDTO_8S);
    }
}






#endif