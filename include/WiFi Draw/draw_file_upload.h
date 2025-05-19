#include <Arduino.h>
#include <DisplayConfig.h>
#include <WiFi/File_upload.h>
#include <drawFileMenu.h>

void draw_wifi_upload_disconnected(){

}
void draw_upload_file_page(){
    if(!WIFI_CONNECTION_STATUS){
        
        while(start_time < end_time){
            ESP.wdtDisable();
        u8g2.clearBuffer();
        
        u8g2.sendBuffer();
    }
        return;
    else{
        initWebUploadServer();
        Serial.print("IP адреса: ");
        Serial.println(WiFi.localIP());
        return_IP_address(ECLIPSE_IP_SERVER);
    }
   
    while(1){
        server.handleClient();
        ESP.wdtDisable();
        u8g2.clearBuffer();
        u8g2.setColorIndex(1);
        draw_directory_info("Upload file");
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setCursor(1, 20); u8g2.printf("Server IP: %s", ECLIPSE_IP_SERVER);
        u8g2.setCursor(1, 30);  u8g2.print("Awaitіng for file...");
        
        if(serial_command() == BACK) break;
        
        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    }
}