#ifndef MAIN_SCREEN_INPTS
#define MAIN_SCREEN_INPTS

#include <UserInputs.h>
#include <Arduino.h>

struct Selected_Icon_Info{
    int select_icon_num = 0;
    bool selected_b = false;
};

Selected_Icon_Info get_select_icon(int command) {
    static int select_icon_num = 0;
    bool selected_b = false; // Ініціалізація за замовчуванням

    switch (command) {
        case LIST_DOWN_MENU:
            select_icon_num++;
            break;
        case LIST_UP_MENU:
            select_icon_num--;
            break;
        case SELECT:
            selected_b = true;
            break;
    }

    if (select_icon_num < 0) select_icon_num = 2;
    if (select_icon_num > 2) select_icon_num = 0;

    return {select_icon_num, selected_b};
}









#endif