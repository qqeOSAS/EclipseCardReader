#ifndef DRAW_CONNECT_TO_WIFI
#define DRAW_CONNECT_TO_WIFI 

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <UserInputs.h>
#include <WiFi/connect_to_WiFi.h>
#include <Icon_animations.h>
#include <File properties browser/draw_file_properties_utils.h>
#include "draw_enter_string_screen.h"

DrawOptionsState drawSSidListState;

void draw_scanning_SSID(){
    unsigned long timer_1 = millis();

    byte progres_bar_widht = 0;
    while(progres_bar_widht < 124){
        ESP.wdtDisable();
        u8g2.clearBuffer();

        u8g2.setColorIndex(1);
        u8g2.drawRFrame(2,50,124,10,1);
        u8g2.drawRBox(2,50,progres_bar_widht,10,1);
        u8g2.drawLine(0,64,128,64);
        u8g2.setColorIndex(0);
        u8g2.drawRFrame(3,52,124,6,1);

        if(millis() - timer_1 >= 10){
            timer_1 = millis();
            progres_bar_widht++;
        }

        draw_directory_info("Scanning for SSIDS");
        draw_anthena_icon_animation();
        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    } 
}
byte draw_enter_WiFi_pasword(char* selected_SSID) {
    strcpy(entered_str.entered_string, ""); // Очищаємо введений рядок
    entered_str.isEntered = false;
    byte connectStat;
    size_t prompt_size = strlen("Enter password for ") + strlen(selected_SSID) + 1; // +1 для '\0'
    char* prompt = (char*)malloc(prompt_size);

    if (prompt == NULL) {
        Serial.println("Failed to allocate memory for prompt");
        return 0; 
    }

    snprintf(prompt, prompt_size, "Enter password for %s", selected_SSID);

    while (1) {
        ESP.wdtDisable();
        entered_str = draw_enter_string_screen(prompt); // Передаємо динамічно створений рядок
        if (entered_str.isEntered) {
            if (entered_str.selected_action == 2) {
                strcpy(entered_str.entered_string, ""); // Очищаємо введений рядок
                entered_str.isEntered = false;
                entered_str.selected_action = 0;
                break;
            }
            if (entered_str.selected_action == 1) {
                entered_str.isEntered = false;
                entered_str.selected_action = 0;
                u8g2.clearBuffer();
                draw_directory_info("Connecting to WiFi...");
                u8g2.sendBuffer();
                connectStat = connect_to_selected_SSID(selected_SSID, entered_str.entered_string);
                break;
            }
        }
        ESP.wdtEnable(WDTO_8S);
    }

    // Звільняємо пам'ять
    free(prompt);

    return connectStat;
}


void draw_after_attempt(byte returned_status,char* selected_SSID,char* entered_password){
    selected_user_option user_opt = {false,0};
    bool exit_loop = false;
    while(1){
        ESP.wdtDisable();
        int command = serial_command();
        u8g2.clearBuffer();
        u8g2.setColorIndex(1);
        draw_directory_info("Connection status");
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setCursor(1,20);
	    u8g2.print("SSID Name: ");
	    u8g2.print(selected_SSID);
        u8g2.setCursor(1,30);
        u8g2.print("Returned status:");
        u8g2.setCursor(1,40);

        switch (returned_status) {
            case WL_CONNECTED: 
                u8g2.print("Connected");
                user_opt = draw_files_properties_menu_user(command,"OK","Save in txt"); 
                break;
            case WL_NO_SSID_AVAIL: u8g2.print("SSID not available"); break;
            case WL_CONNECT_FAILED: u8g2.print("Connection failed"); break;
            case WL_CONNECTION_LOST: u8g2.print("Connection lost"); break;
            case WL_DISCONNECTED: u8g2.print("Disconnected"); break;
            case WL_WRONG_PASSWORD: u8g2.print("Wrong password"); break;
            default: u8g2.print("Unknown status");
        }
        if (returned_status != WL_CONNECTED) user_opt = draw_files_properties_menu_user(command, "OK", "try again");

        if(user_opt.is_selected){
            switch(user_opt.selected_option){
                case OK: exit_loop = true; break;
                case 1:
                    if(returned_status == WL_CONNECTED){
                        create_directory("WiFi_connection_logs");
                        size_t filename_size = strlen(selected_SSID) + strlen("_log.txt") + 1;
                        char* filename = (char*)malloc(filename_size);

                        if (filename == NULL) {
                            Serial.println("Failed to allocate memory for filename");
                            return; 
                        }
                        size_t content_size = strlen("SSID") + strlen(" Log") + 1 + strlen("SSID: ") + strlen(selected_SSID) + 1 + strlen("Pasword: ") + 1 + strlen(entered_password) + 1;
                        char* content = (char*)malloc(content_size);

                        sprintf(content, "SSID Log\nSSID: %s\nPasword: %s", selected_SSID, entered_password);
                        snprintf(filename,filename_size,"%s_log.txt",selected_SSID);
                        Serial.println(filename);
                        Serial.println(content);
                        Serial.println(content_size);
                        create_txt_file("WiFi_connection_logs/",filename,content);
                        free(filename);
                        free(content);
                    }
                    exit_loop = true; 
                    break;
            }
        }

        if(exit_loop) break;
  
        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    }

}

void draw_SSID_info(char* selected_SSID, byte selected_ssid_index){
    selected_user_option user_opt = {false,0};
    bool exit_loop = false;

    size_t prompt_size = strlen(selected_SSID) + 1 + strlen("Info "); // +1 для '\0'
    char* prompt = (char*)malloc(prompt_size);

    if (prompt == NULL) {
        Serial.println("Failed to allocate memory for prompt");
        return; 
    }
    snprintf(prompt, prompt_size, "%s Info", selected_SSID);

    while(1){
        ESP.wdtDisable();
        int command = serial_command();
       
        
        u8g2.clearBuffer();
        draw_directory_info(prompt);
        u8g2.setColorIndex(1);
    
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
	    u8g2.setCursor(1,20);
	    u8g2.print("SSID Name: ");
	    u8g2.print(selected_SSID);
        u8g2.setCursor(1,30);
	    u8g2.print("WiFi RSSI: ");
	    u8g2.print(ssid_list_info.rssiList[selected_ssid_index]);
        u8g2.setCursor(1,40);
	    u8g2.print("Encryption: ");

        switch (ssid_list_info.encryption_type[selected_ssid_index]) {
            case ENC_TYPE_WEP:  u8g2.print("WEP"); break;
            case ENC_TYPE_TKIP: u8g2.print("WPA"); break;
            case ENC_TYPE_CCMP: u8g2.print("WPA2"); break;
            case ENC_TYPE_NONE: u8g2.print("Open network"); break;
            default: u8g2.print("unknown type");
        }
        user_opt = draw_files_properties_menu_user(command,"OK","Connect");
        if(user_opt.is_selected){

            switch(user_opt.selected_option){
                case OK: exit_loop = true; break;
                case 1:
                    byte connection_stat = draw_enter_WiFi_pasword(selected_SSID);
                    draw_after_attempt(connection_stat,selected_SSID,entered_str.entered_string);
                    exit_loop = true;
                break;
                
            }
            if(exit_loop) break;

        }
        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    }
    free(prompt);

}

void draw_ssid_list_menu(){
    u8g2.setBitmapMode(1);
    u8g2.setColorIndex(1);
    draw_directory_info("SSID List");
    drawSSidListState.pageNum = draw_file_names(ssid_list_info.SSID_LIST, ssid_list_info.ssid_to_store, drawSSidListState.result.status,0,1,0,1,0);
    drawSSidListState.selectedFileData = return_select_label(ssid_list_info.SSID_LIST, drawSSidListState.result.command, drawSSidListState.result.y, drawSSidListState.pageNum);

}

void display_SSID_list(){
    unsigned long timer_1 = 0;
    draw_scanning_SSID();
    get_SSID_LIST();
    while(1){
        unsigned long currentMillis = millis();

        ESP.wdtDisable();
        u8g2.clearBuffer();
        draw_ssid_list_menu();
        drawSSidListState.result = draw_selecting_icon(1);

        if(drawSSidListState.result.command == BACK) break;

        if(drawSSidListState.result.command ==  UPDATE_SSIDS){
            Serial.print("START TIME: ");
            Serial.println(millis());
            draw_scanning_SSID();
            get_SSID_LIST();

            Serial.print("End TIME: ");
            Serial.println(millis());

        }
        if(drawSSidListState.selectedFileData.isSelected){
            Serial.print("Selected SSID:");
            Serial.println(drawSSidListState.selectedFileData.fileName);
            bool exist = check_SSID_existing(drawSSidListState.selectedFileData.fileName);
            if(exist)
                draw_SSID_info(drawSSidListState.selectedFileData.fileName,drawSSidListState.selectedFileData.fileIndex);

        }

        u8g2.sendBuffer();


        ESP.wdtEnable(WDTO_8S);
    }
}
#endif


