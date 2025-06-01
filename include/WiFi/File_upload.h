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
	float upload_time_sec = 0;
	bool upload_ended = false;
    bool upload_in_progress = false;
    char filename[30];
    uint64_t size = 0;
    int bytes_per_second = 0;
    uint64_t bytes_alredy_written = 0;
    byte instalation_progress = 0;
};
uploaded_file uploadFileData;

char spinner[] = "|/-\\";

// Глобальна змінна для розміру файлу
unsigned long uploadedFileSize = 0;
////sdsdsadsad
	///
void draw_upload_file_page(unsigned long file_size) {
    spinner[0] = '|';
    spinner[1] = '/';
    spinner[2] = '-';
    spinner[3] = '\\';
    static byte i = 0;
    i = (i + 1) % 4; // Змінюємо індекс від 0 до 3 по колу

    if(uploadFileData.upload_in_progress){
        u8g2.setColorIndex(1);
        draw_directory_info("Uploading file in progress");
        u8g2.setFont(u8g2_font_5x8_t_cyrillic);
        u8g2.setCursor(1, 20); u8g2.printf("File:%s",uploadFileData.filename);
        u8g2.setCursor(1, 30); u8g2.printf("Writing:%llu bytes",uploadFileData.bytes_alredy_written);
        Serial.print(spinner[i]);
    }
}
unsigned long upload_start_time;
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
    draw_upload_file_page(uploadedFileSize); // Використовуємо глобальну змінну
	u8g2.sendBuffer();

    switch(upload.status) {
        case UPLOAD_FILE_START: {
			uploadFileData.upload_in_progress = true;
			uploadFileData.upload_ended = false;
			
			uploadFileData.upload_start_time = millis();
			uploadFileData.bytes_alredy_written = 0;
			uploadFileData.bytes_per_second = 0;
			
			uploadFileData.upload_time_sec = 0;
            writen_bytes = 0;

            strncpy(uploadFileData.filename, upload.filename.c_str(), sizeof(uploadFileData.filename) - 1);
            uploadFileData.filename[sizeof(uploadFileData.filename) - 1] = '\0';
            uploadFileData.size = uploadedFileSize; // <-- тут зберігаємо розмір файлу
            Serial.printf("[UPLOAD] Uploading file: %s, size: %lu\n", uploadFileData.filename, uploadedFileSize);
            create_directory("/Uploads");
            if(!begin_SD()) {
                Serial.println("[UPLOAD] SD card not initialized!");
                return;
            }
            char filename[30];
            strncpy(filename, upload.filename.c_str(), sizeof(filename));
            filename[sizeof(filename)-1] = '\0';
            size_t filepath_size = strlen("/Uploads/") + strlen(filename) + 1;
            char* full_filepath = (char*)malloc(filepath_size);
            sprintf(full_filepath, "/Uploads/%s", filename);

            create_upload_file(uploadFile, full_filepath);
            free(full_filepath);
            if (!uploadFile) {
                Serial.println("[UPLOAD] Failed to open file for writing!");
                return;
            }
            break;
        }
        case UPLOAD_FILE_WRITE: {
            write_upload_file(uploadFile, upload.buf, upload.currentSize);
            Serial.print("[UPLOAD] Writing chunk, size: ");
            Serial.println(upload.currentSize);
            writen_bytes += upload.currentSize;
            uploadFileData.bytes_alredy_written = writen_bytes;
            break;
        }
        case UPLOAD_FILE_END: {
			unsigned long upload_end_time = millis();
			uploadFileData.upload_time_sec = float(float(upload_end_time) - float(uploadFileData.upload_start_time)) / 1000;
			uploadFileData.bytes_per_second = (uploadFileData.bytes_alredy_written / uploadFileData.upload_time_sec);


            uploadFileData.upload_in_progress = false;
			uploadFileData.upload_ended = true;

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

