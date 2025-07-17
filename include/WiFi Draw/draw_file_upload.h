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
void draw_upload_file_finished_succesfully(unsigned long file_size){
	u8g2.setColorIndex(1);
	draw_directory_info("Upload finished succesfully");
	u8g2.setFont(u8g2_font_5x8_t_cyrillic);
	u8g2.setCursor(1, 20); u8g2.printf("File:%s",uploadFileData.filename);
	u8g2.setCursor(1, 30); u8g2.printf("Upload time:%.2f sec",uploadFileData.upload_time_sec);
	u8g2.setCursor(1, 40); u8g2.printf("File size:%llu bytes",uploadFileData.bytes_alredy_written);
    u8g2.setCursor(1, 50); u8g2.printf("Speed:%.2f KB/sec",uploadFileData.speed_Kbytes_per_second);
}
void draw_upload_file_finished_eror(unsigned long file_size){
	u8g2.setColorIndex(1);
	draw_directory_info("Upload eror");
	u8g2.setFont(u8g2_font_5x8_t_cyrillic);
	u8g2.setCursor(1, 20); u8g2.printf("File:%s",uploadFileData.filename);
    u8g2.setCursor(1, 30); u8g2.printf("File have cyrylic name");
    u8g2.setCursor(1, 40); u8g2.printf("Press SELECT to continue");
}
void draw_waiting_for_file(bool upload_mode){
    u8g2.setColorIndex(1);
    draw_directory_info("   Upload file");
    u8g2.setFont(u8g2_font_5x8_t_cyrillic);
    return_IP_address(ECLIPSE_IP_SERVER);
    if(upload_mode){
        u8g2.setCursor(1, 20); u8g2.printf("AP mode active");
        u8g2.setCursor(1, 30); u8g2.printf("Device: %s", ECLIPSE_SSID);
        u8g2.setCursor(1,40); u8g2.printf("Password: %s", ECLIPSE_PASSWORD);
    }
    else{
        u8g2.setCursor(1, 20); u8g2.printf("WiFi mode active");
        u8g2.setCursor(1, 30); u8g2.printf("Server IP: %s", ECLIPSE_IP_SERVER);
    }
    u8g2.setCursor(1, 50);  u8g2.print("Awaitіng for file...");
}

void draw_upload_status(){
    if(uploadFileData.upload_ended_succesfully){
        u8g2.clearBuffer();
        draw_upload_file_finished_succesfully(uploadedFileSize);
        u8g2.sendBuffer();
    }
    if(uploadFileData.error_occurred){
        u8g2.clearBuffer();
        draw_upload_file_finished_eror(uploadedFileSize);
        u8g2.sendBuffer();
    }

}
void draw_WiFi_upload(){
    uploadFileData.upload_ended_succesfully = false;
    if(!WIFI_CONNECTION_STATUS){
        draw_wifi_upload_noWiFi();
        return;
    }
    if(!begin_SD()){
        draw_insert_SD_screen_6_sec();
        return;
    }
    else{
        initWebUploadServer();
        u8g2.clearBuffer();
        draw_waiting_for_file(false);
        u8g2.sendBuffer(); 
    }
    system_update_cpu_freq(160);
    while(1){
        ESP.wdtDisable();
        server.handleClient();

        draw_upload_status();

        switch(serial_command()){
            case BACK:
                server.close();
                dnsServer.stop();
                stop_Eclipse_AP();
                system_update_cpu_freq(80);
                return;
            case SELECT:
                uploadFileData.error_occurred = false;
                u8g2.clearBuffer();
                draw_waiting_for_file(true);
                u8g2.sendBuffer();
                break;
        }
        ESP.wdtEnable(WDTO_8S);
    }
}
void draw_AP_upload(){
    if(!begin_SD()){
        draw_insert_SD_screen_6_sec();
        return;
    }
    create_Eclipse_AP();
    start_dns();
    start_Eclipse_web_server();

    u8g2.clearBuffer();
    draw_waiting_for_file(true);
    u8g2.sendBuffer();

    system_update_cpu_freq(160);
    while(1){
        ESP.wdtDisable();
        dnsServer.processNextRequest();
        server.handleClient();

        draw_upload_status();

        switch(serial_command()){
            case BACK:
                server.close();
                dnsServer.stop();
                stop_Eclipse_AP();
                system_update_cpu_freq(80);
                return;
            case SELECT:
                uploadFileData.error_occurred = false;
                u8g2.clearBuffer();
                draw_waiting_for_file(true);
                u8g2.sendBuffer();
                break;
        }
 
        ESP.wdtEnable(WDTO_8S);
    
    }
}
char file_upload_options[2][30] = { "WiFi upload", "AP upload" };

void draw_select_upload_option_menu(){
    
    while(1){
        ESP.wdtDisable();
        u8g2.clearBuffer();
        u8g2.setBitmapMode(1);
        u8g2.setColorIndex(1);
        draw_directory_info("WiFi files upload menu.Select option");

        if(drawSSidListState.result.command == BACK){
            drawSSidListState.result.command = 0;
            break;
        } 

        drawSSidListState.pageNum = draw_file_names(file_upload_options, 2, drawSSidListState.result.status,0,1,0,1,0);
        drawSSidListState.selectedFileData = return_select_label(file_upload_options, drawSSidListState.result.command, drawSSidListState.result.y, drawSSidListState.pageNum);
        drawSSidListState.result = draw_selecting_icon(1);
        

        if(drawSSidListState.selectedFileData.isSelected){
            if(drawSSidListState.selectedFileData.fileIndex == 0)
                draw_WiFi_upload();

            else if(drawSSidListState.selectedFileData.fileIndex == 1)
                draw_AP_upload();
        }

        u8g2.sendBuffer();
        ESP.wdtEnable(WDTO_8S);
    
}
}