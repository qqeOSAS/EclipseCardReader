#ifndef DRAW_DEAUTH_WIFI
#define DRAW_DEAUTH_WIFI

#include <Arduino.h>
#include <DisplayConfig.h>
#include <WiFi Draw/draw_connect_toWiFi.h>
#include <WiFi/WiFi_deather.h>


void draw_scan_clients(char* selected_SSID, byte selected_ssid_index, long long_scan_time){
    int scan_attempt = 0;
    int all_scan_attempts = long_scan_time / SCAN_CYCLE_DURATION;
    long end_preveiv_time = millis() + 4000;

    while(millis() < end_preveiv_time){
        ESP.wdtDisable();
        u8g2.clearBuffer();
        draw_directory_info("Scanning clients");
        u8g2.setColorIndex(1);
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setCursor(1, 20); u8g2.print("Starting scanning"); 
        u8g2.setCursor(1, 30); u8g2.print("BSSID for clients.."); 
        u8g2.setCursor(1, 40); u8g2.print("Scan duration: "); u8g2.print(long_scan_time / 1000); u8g2.print("s");
        
        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);

    }

    while(scan_attempt < all_scan_attempts){
        ESP.wdtDisable();
        u8g2.clearBuffer();
        draw_directory_info("Scanning clients");
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setColorIndex(1);
        u8g2.setCursor(1, 20); u8g2.print("New clients per scan: "); u8g2.print(scan_clientCount);
        u8g2.setCursor(1, 30); u8g2.print("All found clients: "); u8g2.print(all_known_clients_count);

        u8g2.setCursor(1, 40); u8g2.print("Attempt: "); u8g2.print(scan_attempt);
        u8g2.print(" of ("); 
        u8g2.print(all_scan_attempts);
        u8g2.print(")");
        

        int command = serial_command();

        if(command == BACK) break;
        u8g2.sendBuffer();

        scanClientsInNetwork(ssid_list_info.bssid[selected_ssid_index], ssid_list_info.channel[selected_ssid_index], selected_ssid_index);
        all_known_clients_count = return_all_known_clients_count();
        scan_attempt++;
        for(int i = 0; i < scan_clientCount; i++) {
            Serial.print("Client MAC found: ");
            printMacAddress(knownClients[i].mac);
        }
        Serial.println("All known clients");
        
        for(byte i = 0; i < 15; i++) printMacAddress(knownClients[i].mac);

        ESP.wdtEnable(WDTO_8S);
    }
    do_deauth_attack(ssid_list_info.bssid[selected_ssid_index]);
    clearClients();
}
void draw_deauth_attack(){

}


void draw_mac_address(uint8_t *mac) {
    char macstr[18];
    snprintf(macstr, sizeof(macstr), "%02X:%02X:%02X:%02X:%02X:%02X",mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    u8g2.print(macstr);
}

void display_deauth_ssid_(char* selected_ssid, byte selected_ssid_index){
    selected_user_option user_opt = {false,0};
    bool exit_loop = false;

    size_t prompt_size = strlen(selected_ssid) + 1 + strlen("Info ") + 30; // +1 для '\0'
    char* prompt = (char*)malloc(prompt_size);

    if (prompt == NULL) return; 

    snprintf(prompt, prompt_size, "%s Info.You want to deauth this SSID?", selected_ssid);

    while(1){
        ESP.wdtDisable();
        int command = serial_command();
       
        u8g2.clearBuffer();
        u8g2.setColorIndex(1);
        draw_directory_info(prompt);

        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setCursor(1, 20); u8g2.print("SSID Name: "); u8g2.print(selected_ssid);
        u8g2.setCursor(1, 30); u8g2.print("WiFi RSSI: "); u8g2.print(ssid_list_info.rssiList[selected_ssid_index]);
        u8g2.setCursor(1, 40); u8g2.print("Channel:"); u8g2.print(ssid_list_info.channel[selected_ssid_index]); 
        u8g2.print(" EncType:"); u8g2.print(ssid_list_info.encryption_type[selected_ssid_index]);
        u8g2.setCursor(1, 50); u8g2.print("BSSID: "); draw_mac_address(ssid_list_info.bssid[selected_ssid_index]);

        user_opt = draw_files_properties_menu_user(command,"OK","Scan clients");
        if(user_opt.is_selected){
            switch(user_opt.selected_option){
                case 0: 
                    exit_loop = true;
                    break;

                case 1:
                draw_scan_clients(ssid_list_info.SSID_LIST[selected_ssid_index],selected_ssid_index,60000);
                    
                    break;
            }
        }
        if(exit_loop) break;

        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    }
    free(prompt);

}


void display_select_death_ssid(){
    get_SSID_LIST();
    while(1){
        ESP.wdtDisable();
        u8g2.clearBuffer();
        draw_ssid_list_menu("Select deauth taget");
        drawSSidListState.result = draw_selecting_icon(1);
        if(drawSSidListState.result.command == BACK) break;

        if(drawSSidListState.result.command ==  UPDATE_SSIDS){
            draw_scanning_SSID();
            get_SSID_LIST();

        }
        if(drawSSidListState.selectedFileData.isSelected){
            Serial.print("Selected SSID:");
            Serial.println(drawSSidListState.selectedFileData.fileName);
            Serial.print("FILE INDEXXXXXXXXXXXXXXXXXXXX");
            Serial.println(drawSSidListState.selectedFileData.fileIndex);
            bool exist = check_SSID_existing(drawSSidListState.selectedFileData.fileName);
            //if(exist){
                display_deauth_ssid_(drawSSidListState.selectedFileData.fileName, drawSSidListState.selectedFileData.fileIndex);
                break;
            //}
                

        }

        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);


    }



}










#endif