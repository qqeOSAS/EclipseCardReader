#ifndef BUTTON_CON
#define BUTTON_CON

#include <Arduino.h>
#include <GyverButton.h>

#define LIST_UP_BTN_PIN 16
#define LIST_DOWN_BTN_PIN 2
#define SELECT_BTN_PIN 0

GButton listUP_btn(LIST_UP_BTN_PIN);
GButton listDown_btn(LIST_DOWN_BTN_PIN);
GButton Select_btn(SELECT_BTN_PIN);

void set_BTN_config(){

    listUP_btn.setDebounce(5);
	listUP_btn.setTimeout(1000);
	listUP_btn.setClickTimeout(70);
	listUP_btn.setType(HIGH_PULL);
	listUP_btn.setDirection(NORM_OPEN);
    listUP_btn.setTickMode(MANUAL);

    listDown_btn.setDebounce(5);
	listDown_btn.setTimeout(1000);
	listDown_btn.setClickTimeout(70);
	listDown_btn.setType(HIGH_PULL);
	listDown_btn.setDirection(NORM_OPEN);
    listDown_btn.setTickMode(MANUAL);

   	Select_btn.setDebounce(50);
	Select_btn.setTimeout(500);
	Select_btn.setClickTimeout(100);
	Select_btn.setType(HIGH_PULL);
	Select_btn.setDirection(NORM_OPEN);
    Select_btn.setTickMode(MANUAL);




}










#endif