#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <WiFi/Wifi_config.h>
#include <DNSServer.h>
#include <SdCard_utils.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include "File_upload_html.h"

ESP8266WebServer server(80);
SdFile uploadFile;
DNSServer dnsServer;

struct uploaded_file{
	unsigned long upload_start_time = 0;
    unsigned long upload_end_time = 0;
	float upload_time_sec = 0;
	bool upload_ended_succesfully = false;
    bool error_occurred;
    bool upload_in_progress = false;
    char filename[30];
    float speed_Kbytes_per_second = 0;
    uint64_t bytes_alredy_written = 0;
};
uploaded_file uploadFileData;


// Глобальна змінна для розміру файлу
unsigned long uploadedFileSize = 0;
////sdsdsadsad
	///
void draw_upload_file_page() {
    if(uploadFileData.upload_in_progress){
        u8g2.setColorIndex(1);
        draw_directory_info("Uploading file in progress");
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setCursor(1, 20); u8g2.printf("File:%s",uploadFileData.filename);
        u8g2.setCursor(1, 30); u8g2.printf("Writing:%llu bytes",uploadFileData.bytes_alredy_written);
    }
}
void create_Eclipse_AP() {
    WiFi.softAP(ECLIPSE_SSID, ECLIPSE_PASSWORD);
    delay(100);
    IPAddress myIP = WiFi.softAPIP();
    Serial.printf("AP IP address: %s\n", myIP.toString().c_str());
}
void start_dns() {
    IPAddress myIP = WiFi.softAPIP();
    dnsServer.start(53, "*", myIP);
    Serial.println("DNS server started (captive portal mode).");
}
void stop_Eclipse_AP() {
    WiFi.softAPdisconnect(true);
    Serial.println("AP вимкнено.");
}

void handleFileUpload() {
    HTTPUpload& upload = server.upload();
	ESP.wdtDisable();
    static unsigned long writen_bytes = 0;
    u8g2.clearBuffer();
    draw_upload_file_page(); // Використовуємо глобальну змінну
	u8g2.sendBuffer();
    
    byte upload_status = upload.status;
    if(uploadFileData.error_occurred)
        return;

    switch(upload_status) {
        case UPLOAD_FILE_START: {
            uploadFileData.error_occurred = false;
			uploadFileData.upload_in_progress = true;
			uploadFileData.upload_ended_succesfully = false;
			
			uploadFileData.upload_start_time = millis();
			uploadFileData.bytes_alredy_written = 0;
			uploadFileData.speed_Kbytes_per_second = 0;
			uploadFileData.upload_time_sec = 0;
            writen_bytes = 0;

            strncpy(uploadFileData.filename, upload.filename.c_str(), sizeof(uploadFileData.filename) - 1);
            uploadFileData.filename[sizeof(uploadFileData.filename) - 1] = '\0';

            create_directory("/Uploads");
            
            size_t filepath_size = strlen("/Uploads/") + strlen(uploadFileData.filename) + 1;
            char* full_filepath = (char*)malloc(filepath_size);
            sprintf(full_filepath, "/Uploads/%s", uploadFileData.filename);

            create_upload_file(uploadFile, full_filepath);
            free(full_filepath);
            if (!uploadFile) {
                Serial.println("[UPLOAD] Failed to open file for writing!");
                upload_status = UPLOAD_FILE_ABORTED;
                uploadFileData.error_occurred = true;
                uploadFileData.upload_in_progress = false;
                uploadFileData.upload_ended_succesfully = false;
                return;
            }
            break;
        }
        case UPLOAD_FILE_WRITE: {
            write_upload_file(uploadFile, upload.buf, upload.currentSize);
            Serial.printf("[UPLOAD] Writing chunk, size:%lu bytes\n", upload.currentSize);
            writen_bytes += upload.currentSize;
            uploadFileData.bytes_alredy_written = writen_bytes;
            break;
        }
        case UPLOAD_FILE_END: {
			uploadFileData.upload_end_time = millis();
			uploadFileData.upload_time_sec = (uploadFileData.upload_end_time - uploadFileData.upload_start_time) / 1000.0; // Перетворюємо в секунди

            // Обчислюємо швидкість запису
            uploadFileData.speed_Kbytes_per_second = (float)uploadFileData.bytes_alredy_written / uploadFileData.upload_time_sec / 1024.0f; // Перетворюємо в КБ/с


            uploadFileData.upload_in_progress = false;
			uploadFileData.upload_ended_succesfully = true;

            if (uploadFile) {
                uploadFile.close();
                Serial.println("[UPLOAD] File upload finished and closed!");
            }
            Serial.print("[UPLOAD] Total size: ");
            Serial.println(writen_bytes); // показуємо скільки реально записано
            break;
        }
        case UPLOAD_FILE_ABORTED: {
            Serial.println("[UPLOAD] Upload aborted!");
            if (uploadFile) uploadFile.close();
            break;
        }
        default: {
            Serial.println("[UPLOAD] Unknown upload status!");
            break;
        }
    }
	ESP.wdtEnable(WDTO_8S);
}

void handleroot(){
    server.send(200, "text/html", uploadPage);
}

void initWebUploadServer() {
    server.on("/", HTTP_GET, handleroot);

    server.on(
        "/upload", HTTP_POST,
        []() {
            // Зчитуємо розмір файлу з форми ОДИН раз перед upload
            String fileSizeStr = server.arg("size");
            uploadedFileSize = fileSizeStr.toInt();
            Serial.printf("Uploaded file size (from form): %lu bytes\n", uploadedFileSize);

            server.send(200, "text/html",
                "<html><head><style>"
                "body{font-family:sans-serif;background:#f4f4f4;text-align:center;padding-top:50px;}"
                ".msg{background:#fff;padding:30px 40px;border-radius:8px;display:inline-block;box-shadow:0 2px 8px #ccc;}"
                "a{display:block;margin-top:20px;color:#2196F3;text-decoration:none;font-weight:bold;}"
                "</style></head><body>"
                "<div class='msg'><h2>File uploaded!</h2>"
                "<a href='/'>Back</a></div>"
                "</body></html>");
        },
        handleFileUpload
    );

    server.begin();
    Serial.println("✅ Web server started.");
}
void start_Eclipse_web_server() {
    server.on("/", HTTP_GET, handleroot);

    // Обробник upload POST (з розміром файлу)
    server.on("/upload", HTTP_POST,
        []() {
            String fileSizeStr = server.arg("size");
            uploadedFileSize = fileSizeStr.toInt();
            Serial.printf("Uploaded file size (from form): %lu bytes\n", uploadedFileSize);

            server.send(200, "text/html",
                "<html><head><style>"
                "body{font-family:sans-serif;background:#f4f4f4;text-align:center;padding-top:50px;}"
                ".msg{background:#fff;padding:30px 40px;border-radius:8px;display:inline-block;box-shadow:0 2px 8px #ccc;}"
                "a{display:block;margin-top:20px;color:#2196F3;text-decoration:none;font-weight:bold;}"
                "</style></head><body>"
                "<div class='msg'><h2>File uploaded!</h2>"
                "<a href='/'>Back</a></div>"
                "</body></html>");
        },
        handleFileUpload
    );

    // Перенаправлення всіх інших запитів на upload-сторінку (captive portal)
    server.onNotFound(handleroot);

    server.begin();
    Serial.println("✅ Web server started.");
}

void return_IP_address(char* ip_buffer){
    IPAddress ip = WiFi.localIP();
    strncpy(ip_buffer, ip.toString().c_str(), 16); // Копіюємо IP-адресу в буфер
    ip_buffer[15] = '\0'; // Гарантія завершення рядка
}

