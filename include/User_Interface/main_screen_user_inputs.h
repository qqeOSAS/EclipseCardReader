#ifndef MAIN_SCREEN_INPTS
#define MAIN_SCREEN_INPTS

#include <UserInputs.h>
#include <Arduino.h>

struct Selected_Icon_Info{
    int select_icon_num = 0;
    bool selected_b = false;
    bool draw_anim1 = false;
    bool draw_anim2 = false;
    bool draw_anim3 = false;
};

Selected_Icon_Info get_select_icon(int command) {
    static int select_icon_num = 0;
    bool selected_b = false;
    bool draw_anim1 = false;
    bool draw_anim2 = false;
    bool draw_anim3 = false; // Ініціалізація за замовчуванням


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
    
    switch(select_icon_num){
        case 0:
            draw_anim1 = true; 
            break;
        case 1:
            draw_anim2 = true; break;
        case 3:
            draw_anim3 = true; break;
    }

    if (select_icon_num < 0) select_icon_num = 2;
    if (select_icon_num > 2) select_icon_num = 0;

    return {select_icon_num, selected_b,draw_anim1,draw_anim2,draw_anim3};
}









#endif