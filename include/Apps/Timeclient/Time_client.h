#ifndef TIME_CLIENT_H
#define TIME_CLIENT_H

#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>


WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pool.ntp.org", 10800, 60000); 
struct time_info{
    int day;
    int hours;
    int minutes;
    int seconds;
};
time_info time_data;
void initTimeClient() {
    timeClient.begin();
    timeClient.setTimeOffset(10800); // UTC+3 for Ukraine
    timeClient.update();
}
void getTime() {
    timeClient.update();
	time_data.day = timeClient.getDay();
	time_data.hours = timeClient.getHours();	
	time_data.minutes= timeClient.getMinutes();

}	












#endif