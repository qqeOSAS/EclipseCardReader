#include <Arduino.h>
#include <DisplayConfig.h>
#include <WiFi/File_upload.h>
#include <drawFileMenu.h>

void draw_wifi_upload_noWiFi(){
    long start_time = millis();
    long end_time = start_time + 5000;
    
    while(start_time < end_time){
        start_time = millis();
        ESP.wdtDisable();

        u8g2.clearBuffer();
        draw_directory_info("No WiFi connection");
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setCursor(1, 20); u8g2.printf("Please connect to WiFi");
        u8g2.setCursor(1, 30); u8g2.print("and try again");
        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    }

}
void draw_upload(){
    if(!WIFI_CONNECTION_STATUS){
        draw_wifi_upload_noWiFi();
        return;
    }
    else{
        initWebUploadServer();
        Serial.print("IP адреса: ");
        Serial.println(WiFi.localIP());
        return_IP_address(ECLIPSE_IP_SERVER);
         u8g2.clearBuffer();
        u8g2.setColorIndex(1);
            draw_directory_info("Upload file");
            u8g2.setFont(u8g2_font_5x8_t_cyrillic);
            u8g2.setCursor(1, 20); u8g2.printf("Server IP: %s", ECLIPSE_IP_SERVER);
            u8g2.setCursor(1, 30);  u8g2.print("Awaitіng for file...");
             u8g2.sendBuffer(); 
    }
   
    while(1){

        ESP.wdtDisable();
       
        
       
        server.handleClient();
        ESP.wdtEnable(WDTO_8S);
        if (serial_command() == BACK) {
            server.close();
            break;
        }
    }
}