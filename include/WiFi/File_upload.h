#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <WiFi/Wifi_config.h>

const char uploadPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>File Upload</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background-color: #f4f4f4;
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
      background-color: #4CAF50;
      color: white;
      padding: 10px 15px;
      border: none;
      border-radius: 5px;
      cursor: pointer;
    }
    input[type="submit"]:hover {
      background-color: #45a049;
    }
  </style>
</head>
<body>
  <h2>Upload a File to ESP8266</h2>
  <form method="POST" action="/upload" enctype="multipart/form-data">
    <input type="file" name="upload" required><br>
    <input type="submit" value="Upload">
  </form>
</body>
</html>
)rawliteral";


ESP8266WebServer server(80);
void handleFileUpload() {
  
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

