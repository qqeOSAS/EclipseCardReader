#ifndef DRAW_FLOOD_ATTACK
#define DRAW_FLOOD_ATTACK


#include <Arduino.h>
#include <DisplayConfig.h>
#include <WiFi Draw/draw_connect_toWiFi.h>
#include <WiFi/Beacon_flood_attack.h>


char flood_attack_vars[][30] = {
    "Real SSID cloning",
    "Fake SSID generating",
   
};
void draw_fake_ssid_flooding(){

    init_flood_attack(false);
    byte minutes = 10;
    int seconds = 1;
    int packets;
    int filtered_packets = 0;
    unsigned long timer_1  = 0;
    while(1){
        ESP.wdtDisable();
        unsigned long currentMillis = millis();

        if(currentMillis - timer_1 >= 1000){
            timer_1 = currentMillis;
            seconds--;
            if(seconds < 0){
                seconds = 60;
                minutes--;
            }
        }
        if(minutes == 0 && seconds == 0) break;
        

        packets = run_flood_attack(true, 250, 0,"");
        if(packets > 0)
            filtered_packets = packets;
        
        u8g2.clearBuffer();
        draw_directory_info("Fake SSID generating");
        u8g2.setColorIndex(1);
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setCursor(1, 20); u8g2.print("Creating 250 fake SSIDs...");
        u8g2.setCursor(1, 30);  u8g2.print(filtered_packets); u8g2.print(" packets per sec");
        u8g2.setCursor(1, 40); u8g2.print("Overheat timer:"); u8g2.print(minutes); u8g2.print(":"); u8g2.print(seconds);
        u8g2.setCursor(1, 50); u8g2.print("Press back to stop flooding");
        u8g2.setCursor(0, 60); u8g2.print("Remember.Atack is illegal!");

        if(serial_command() == BACK) break;
        
        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    }
}
//returns selected ssid index
int draw_select_target_ssid(){
    bool exit_loop = false;
    get_SSID_LIST();
    while(1){
        ESP.wdtDisable();
        u8g2.clearBuffer();
        draw_ssid_list_menu("Select target SSID for copy and flooding");
        drawSSidListState.result = draw_selecting_icon(1);

        if(drawSSidListState.result.command == BACK){
            exit_loop = true;
            break;
        } 

        if(drawSSidListState.result.command ==  UPDATE_SSIDS)
            get_SSID_LIST();
        
        if(drawSSidListState.selectedFileData.isSelected)
           break;
        
        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    }

    if(exit_loop) return -1;

    return drawSSidListState.selectedFileData.fileIndex;
};

void draw_realSSID_flooding(){
    int ssid_index = draw_select_target_ssid();
    
    init_flood_attack(false);
    byte minutes = 10;
    int seconds = 1;
    int packets;
    int filtered_packets = 0;
    unsigned long timer_1  = 0;

    while(1){
        ESP.wdtDisable();

        unsigned long currentMillis = millis();

        if(currentMillis - timer_1 >= 1000){
            timer_1 = currentMillis;
            seconds--;
            if(seconds < 0){
                seconds = 60;
                minutes--;
            }
        }
        if(minutes == 0 && seconds == 0) break;
        

        packets = run_flood_attack(1, 250, 1, ssid_list_info.SSID_LIST[ssid_index]);
        if(packets > 0)
            filtered_packets = packets;

        u8g2.clearBuffer();
        draw_directory_info("Real SSID clonning");
        u8g2.setColorIndex(1);
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setCursor(1, 20); u8g2.print("Creating "); u8g2.print(drawSSidListState.selectedFileData.fileName);
        u8g2.setCursor(1, 30);  u8g2.print(filtered_packets); u8g2.print(" packets per sec");
        u8g2.setCursor(1, 40); u8g2.print("Overheat timer:"); u8g2.print(minutes); u8g2.print(":"); u8g2.print(seconds);
        u8g2.setCursor(1, 50); u8g2.print("Press back to stop flooding");
        u8g2.setCursor(0, 60); u8g2.print("Remember.Atack is illegal!");

        if(serial_command() == BACK) break;


        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    }
}
void draw_prepared_ssid_flooding(){
    init_flood_attack(false);
    byte minutes = 10;
    int seconds = 1;
    int packets;
    int filtered_packets = 0;
    unsigned long timer_1  = 0;
    char* file_content = read_txt_list_file("/Sys_Files", "names.txt");
    if (file_content) {
        //Serial.println("File content successfully read:");
       // Serial.println(file_content);

        // Не забудьте звільнити пам'ять після використання
        free(file_content);
    } else {
        Serial.println("Failed to read file content");
    }

    
}

void draw_select_flood_attack_menu(){
    while(1){
        ESP.wdtDisable();
        u8g2.clearBuffer();
        u8g2.setBitmapMode(1);
        u8g2.setColorIndex(1);
        draw_directory_info("Flood attack menu.Select attack type");

        if(drawSSidListState.result.command == BACK){
            drawSSidListState.result.command = 0;
            break;

        } 

        drawSSidListState.pageNum = draw_file_names(flood_attack_vars, 2, drawSSidListState.result.status,0,1,0,1,0);
        drawSSidListState.selectedFileData = return_select_label(flood_attack_vars, drawSSidListState.result.command, drawSSidListState.result.y, drawSSidListState.pageNum);
        drawSSidListState.result = draw_selecting_icon(1);
        

        if(drawSSidListState.selectedFileData.isSelected){
            Serial.print("Selected attack: ");
            Serial.println(drawSSidListState.selectedFileData.fileName);
            if(drawSSidListState.selectedFileData.fileIndex == 0)
                draw_realSSID_flooding();

            
            else if(drawSSidListState.selectedFileData.fileIndex == 1)
                draw_fake_ssid_flooding();
            
        }

        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    }
}





#endif