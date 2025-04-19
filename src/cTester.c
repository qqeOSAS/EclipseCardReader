#include <stdio.h>
#include <string.h>

char* read_token(char* str, const char* delim) {
    // Використовуємо strtok для отримання токена
    char* token = strtok(str, delim);
    if (token != NULL) {
        printf("Current token: %s\n", token);
    }
    return token;
}

int main() {
    char ssids[] = "Net_01,FreeWiFi,HomeNetwork,SchoolWiFi,Library_Zone,Shop_WiFi,GuestNet,Starbucks_Free,MyPhoneHotspot,Router123,GalaxyS21,AndroidAP,TPLink_5G,Xiaomi_Redmi,Netgear5G,LinksysGuest,AirportWiFi,CafeNet,WorkWiFi,OfficeNet,IoT_Network,Gym_WiFi,HotelFreeWiFi,PublicNet,HiddenSSID,FakeWiFi1,FakeWiFi2,WifiZone,SuperNet_3000,CyberCafe,SecureLine,SpeedyNet,UndergroundWiFi,DroneNet,CampusWiFi,School_Guest,ClassroomAP,OpenAccess,RouterBackup,TestSSID";

    char *token;

    // Отримуємо перший токен
    token = read_token(ssids, ",");

    // Цикл для отримання наступних токенів
    while (token != NULL) {
        token = read_token(NULL, ",");
    }

    return 0;
}