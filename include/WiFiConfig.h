#ifndef WIFI_CONF
#define WIFI_CONF

#include <Arduino.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID TP_Link_2721
#define PASWORD 60764997

void BeginWiFi(char* ssid, char* password) {
    Serial.print("Підключаюсь до WiFi мережі: ");
    Serial.println(ssid);
    Serial.print("З паролем: ");
    Serial.println(password);
    
    
}












#endif