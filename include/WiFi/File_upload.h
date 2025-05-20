#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <WiFi/Wifi_config.h>
#include <SdCard_utils.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>

ESP8266WebServer server(80);
SdFile uploadFile;
struct uploaded_file{
	bool upload_in_progress = false;
  	char filename[30];
  	uint64_t size = 0;
  	int bytes_per_second = 0;
  	uint64_t bytes_alredy_written = 0;
  	byte instalation_progress = 0;
};
uploaded_file uploadFileData;

char spinner[] = "|/-\\";


void draw_upload_file_page(){
	spinner[0] = '|';
	spinner[1] = '/';
	spinner[2] = '-';
	spinner[3] = '\\';
		static byte i = 0;

		i = (i + 1) % 4; // Змінюємо індекс від 0 до 3 по колу
        ESP.wdtDisable();
        if(uploadFileData.upload_in_progress){
			u8g2.setColorIndex(1);
            draw_directory_info("Uploading file in progress");
            u8g2.setFont(u8g2_font_5x8_t_cyrillic);
            u8g2.setCursor(1, 20); u8g2.printf("File:%s",uploadFileData.filename);
            u8g2.setCursor(1, 30); u8g2.printf("Writing:%d bytes",uploadFileData.bytes_alredy_written);
			Serial.print(spinner[i]);
        }
        else{
            u8g2.setColorIndex(1);
            draw_directory_info("Upload file");
            u8g2.setFont(u8g2_font_5x8_t_cyrillic);
            u8g2.setCursor(1, 20); u8g2.printf("Server IP: %s", ECLIPSE_IP_SERVER);
            u8g2.setCursor(1, 30);  u8g2.print("Awaitіng for file...");

        }

        
        
        
        ESP.wdtEnable(WDTO_8S);
}

const char uploadPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>File Upload</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color:rgb(234, 230, 230);
      display: flex;
      flex-direction: column;
      align-items: center;
      padding-top: 50px;
    }
    h2 {
      color: #333;
    }
    form {
      background: white;
      padding: 20px;
      border-radius: 10px;
      box-shadow: 0 0 10px rgba(0,0,0,0.1);
    }
    input[type="file"] {
      margin-bottom: 10px;
    }
    input[type="submit"] {
      background-color:rgb(6, 81, 22);
      color: white;
      padding: 10px 15px;
      border: none;
      border-radius: 5px;
      cursor: pointer;
    }
    input[type="submit"]:hover {
      background-color:rgb(102, 189, 214);
    }
  </style>
</head>
<body>
  <h2>Upload a File to EclipseCardReader</h2>
  <form method="POST" action="/upload" enctype="multipart/form-data">
    <input type="file" name="upload" required><br>
    <input type="submit" value="Upload">
  </form>
</body>
</html>
)rawliteral";



void handleFileUpload() {
    HTTPUpload& upload = server.upload();
	static unsigned long writen_bytes = 0;
	u8g2.clearBuffer();
	draw_upload_file_page();

    switch(upload.status) {
        case UPLOAD_FILE_START: {
			writen_bytes = 0;

      		strncpy(uploadFileData.filename, upload.filename.c_str(), sizeof(uploadFileData.filename) - 1);
      		uploadFileData.filename[sizeof(uploadFileData.filename) - 1] = '\0';
			uploadFileData.size = upload.totalSize;
			Serial.printf("[UPLOAD] Uploading file: %s, size: %d\n", uploadFileData.filename, upload.totalSize);
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
			uploadFileData.upload_in_progress = true;
            write_upload_file(uploadFile, upload.buf, upload.currentSize);
            Serial.print("[UPLOAD] Writing chunk, size: ");
            Serial.println(upload.currentSize);
			writen_bytes += upload.currentSize;
			uploadFileData.bytes_alredy_written = writen_bytes;

            break;
        }
        case UPLOAD_FILE_END: {
            if (uploadFile) {
                uploadFile.close();
                Serial.println("[UPLOAD] File upload finished and closed!");
            }
            Serial.print("[UPLOAD] Total size: ");
            Serial.println(upload.totalSize);
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
	u8g2.sendBuffer();
}

void handleroot(){
    server.send(200, "text/html", uploadPage);
}

void initWebUploadServer() {
  server.on("/", HTTP_GET, handleroot); // <-- Ось тут!

  server.on(
    "/upload", HTTP_POST,
    []() {
      server.send(200, "text/plain", "OK");
    },
    handleFileUpload
  );

  server.begin();
  Serial.println("Веб-сервер запущено.");
}
void return_IP_address(char* ip_buffer){
    IPAddress ip = WiFi.localIP();
    strncpy(ip_buffer, ip.toString().c_str(), 16); // Копіюємо IP-адресу в буфер
    ip_buffer[15] = '\0'; // Гарантія завершення рядка
}

