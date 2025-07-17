#ifndef WiFi_AUTO_CONNECT_H
#define WiFi_AUTO_CONNECT_H


#include <Arduino.h>
#include "connect_to_WiFi.h"
#include <SdCard_utils.h>
#include <utils/String_utils.h>
#include <utils/Read_system_files.h>
#include <utils/draw_boot_messages.h>

struct found_networks {
    char* log_filename;
    char* ssid;
};



byte find_matching_networks(char* log_networks[], int log_network_count, struct found_networks* results, int max_results) {
    int found = 0;

    Serial.printf("Scanning %d log entries for matches...\n", log_network_count);

    for (int i = 0; i < log_network_count; ++i) {
        char* log_WiFi_name = (char*)malloc(30);
        extractWiFiNameFromLogName(log_networks[i], log_WiFi_name, 30);

        Serial.printf("Checking log: '%s'\n", log_WiFi_name);

        char* screen_line = (char*)malloc(64);

        snprintf(screen_line, 64, "Checking: %s", log_WiFi_name);
        draw_boot_one_line_message(screen_line,500);
       

        for (int j = 0; j < 10; ++j) {
            ESP.wdtDisable();
            Serial.printf("  Comparing with SSID[%d]: '%s'... ", j, ssid_list_info.SSID_LIST[j]);

            if (strcmp(log_WiFi_name, ssid_list_info.SSID_LIST[j]) == 0) {
                Serial.println("MATCH");
                draw_boot_3_line_message("[INFO] Found match!", ssid_list_info.SSID_LIST[j], log_networks[i], 400);

                if (found < max_results) {
                    results[found].ssid = ssid_list_info.SSID_LIST[j];
                    results[found].log_filename = log_networks[i];
                    found++;
                }
                else 
                    Serial.println("Max match count reached.");
                
                break;
            } 
            else 
                Serial.println("no match.");
            ESP.wdtEnable(WDTO_8S);
            
        }

        free(log_WiFi_name);
        free(screen_line);
    }

    return found;
}




void auto_connect_to_wifi() {
    ESP.wdtDisable();
    draw_boot_one_line_message(" == WiFi auto-connect ==", 1000);
    
    if (!begin_SD()){
        draw_boot_one_line_message("[ERR] SD Card not initialized!", 1000);
        return;
    }



    draw_boot_one_line_message("[INFO] Scanning WiFi...", 100);
    get_SSID_LIST();

    u8g2.clearBuffer();
    for(byte i = 0; i < 10; i++) {
        u8g2.setCursor(0, 8 + i * 10);
        u8g2.printf("[%d]: ", i + 1);
        u8g2.print(ssid_list_info.SSID_LIST[i]);
        u8g2.printf(" (RSSI: %d)", ssid_list_info.rssiList[i]);
        
        delay(200);
        u8g2.sendBuffer();
    }



    byte logs_count = return_directory_file_count("/WiFi_connection_logs");
    char* logs_names[logs_count];

    for (int i = 0; i < logs_count; i++) {
        logs_names[i] = (char*)malloc(30);
    }

    Files_list_new("/WiFi_connection_logs", logs_names, logs_count);

    draw_boot_one_line_message("[INFO] Matching logs...", 1000);
    found_networks matched_networks[logs_count];
    byte found_count = find_matching_networks(logs_names, logs_count, matched_networks, logs_count);

    if (found_count > 0) {
        ESP.wdtDisable();
        for (byte i = 0; i < found_count; i++) {

            size_t screen_line_size = 64 + (matched_networks[i].ssid ? strlen(matched_networks[i].ssid) : 0);
            char* screen_line = (char*)malloc(screen_line_size);
            snprintf(screen_line, screen_line_size, "SSID: %s", matched_networks[i].ssid);
            draw_boot_one_line_message(screen_line, 800);
            char* extracted_password = read_Wifi_log_file("WiFi_connection_logs", matched_networks[i].log_filename);

            if (extracted_password != NULL) {
                draw_boot_3_line_message("[INFO] CONNECTING....",matched_networks[i].ssid,extracted_password, 500);
                connect_to_selected_SSID(matched_networks[i].ssid, extracted_password);
                free(extracted_password);
                draw_boot_one_line_message("[OK] Connected.", 500);
                break;
            }
            else 
                draw_boot_one_line_message("[ERR] No password found in log file.", 1000);
            
            free(screen_line);
        }
        ESP.wdtEnable(WDTO_8S);
    }
    else 
        draw_boot_one_line_message("[ERR] No matching networks found in logs.", 1000);

    for (int i = 0; i < logs_count; i++) {
        free(logs_names[i]);
    }

    ESP.wdtEnable(WDTO_8S);
}






#endif // WiFi_AUTO_CONNECT_H