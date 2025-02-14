#ifndef USER_INPTS
#define USER_INPTS

#include <Arduino.h>
#include <Serialcomands.h>
#include <ButtonsConfig.h>



// Оголошення функції
int serial_command();



// Реалізація функції
int serial_command() {

    Serial.setTimeout(10);
    if (Serial.available() > 0) {
        String commandStr = Serial.readStringUntil('\n');  // Зчитуємо до нового рядка
        int command = commandStr.toInt();                 // Конвертуємо у число
        return command;
    }

    listDown_btn.tick();
    listUP_btn.tick();
    Select_btn.tick();
    
    if(listUP_btn.isClick()){
        listUP_btn.resetStates();
        return LIST_UP_MENU;
    }

    if(listDown_btn.isClick()){
        listDown_btn.resetStates();
        return LIST_DOWN_MENU;
    }
    if(Select_btn.isClick()){
        Select_btn.resetStates();
        return SELECT;
    }
    if(Select_btn.isHold()){
        Select_btn.resetStates();
        return BACK;
    }
    if(listDown_btn.isHold()){
        listDown_btn.resetStates();
        return OPEN_PLAYER;
    }

    return 0;
 }


#endif  // USER_INPTS
