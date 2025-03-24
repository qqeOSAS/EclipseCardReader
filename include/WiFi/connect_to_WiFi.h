#ifndef CONNECT_TO_WIFI
#define CONNECT_TO_WIFI

#include <Arduino.h>
#include <ESP8266WiFi.h>
struct SSID_LIST_INFO{
    char SSID_LIST[20][30]; // Assuming a maximum of 10 SSIDs
    int rssiList[20];
    byte encryption_type[20];
    int ssid_to_store;

};
SSID_LIST_INFO ssid_list_info;

void bubbleSort_SSID(SSID_LIST_INFO &ssid_list_info) {
    for (int i = 0; i < ssid_list_info.ssid_to_store - 1; i++) {
        for (int j = 0; j < ssid_list_info.ssid_to_store - i - 1; j++) {
            // Якщо потужність сигналу наступної мережі більша, ніж поточної, то обміняти місцями
            if (ssid_list_info.rssiList[j] < ssid_list_info.rssiList[j + 1]) {
                // Обмін значеннями RSSI
                int tempRssi = ssid_list_info.rssiList[j];
                ssid_list_info.rssiList[j] = ssid_list_info.rssiList[j + 1];
                ssid_list_info.rssiList[j + 1] = tempRssi;

                // Обмін значеннями SSID
                char tempSsid[30];
                strcpy(tempSsid, ssid_list_info.SSID_LIST[j]);
                strcpy(ssid_list_info.SSID_LIST[j], ssid_list_info.SSID_LIST[j + 1]);
                strcpy(ssid_list_info.SSID_LIST[j + 1], tempSsid);
            }
        }
    }
}

void get_SSID_LIST(){
    int aviable_network = WiFi.scanNetworks(0,1,0,NULL);
    if(aviable_network  > 0){
        ssid_list_info.ssid_to_store = min(aviable_network,10);
        for(byte i = 0; i < ssid_list_info.ssid_to_store;  i++){
            ssid_list_info.rssiList[i] = WiFi.RSSI(i);
            sprintf(ssid_list_info.SSID_LIST[i], "%s", WiFi.SSID(i).c_str());
            ssid_list_info.encryption_type[i] = WiFi.encryptionType(i);
        }
        bubbleSort_SSID(ssid_list_info);
    }

}
bool check_SSID_existing(const char* selected_SSID){
    int n = WiFi.scanNetworks();

    for (int i = 0; i < n; i++) {
        if (strcmp(WiFi.SSID(i).c_str(), selected_SSID) == 0) 
            return true;
    }
    return false;
}

byte connect_to_selected_SSID(char* selected_SSID, char* password){
    WiFi.setHostname("EclipseDevice");
    WiFi.mode(WIFI_STA); 
    WiFi.begin(selected_SSID, password);  // Підключаємося
    unsigned long start_time = millis();
    unsigned long end_time = start_time + 20000;  // 10 секунд на підключення
    while (WiFi.status() != WL_CONNECTED && start_time < end_time) {
        delay(500);
        ESP.wdtDisable();
        Serial.println(".");
        start_time = millis();
        ESP.wdtEnable(WDTO_8S);
    }
    return WiFi.status();
}

#endif