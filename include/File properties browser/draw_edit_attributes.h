#ifndef DRAW_EDIT_ATTRIBUTES
#define DRAW_EDIT_ATTRIBUTES

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <SdCard_utils.h>


struct selected_user_choice{
    bool is_selected = false;
    byte selected_option = 0;
};
selected_user_choice draw_edit_attrib_menu_user(int command){
    selected_user_choice user_choice = {false, 0};
    static int8 selected_icon = 0;

    switch (command) {
        case SELECT:
            user_choice.is_selected = true;
            user_choice.selected_option = selected_icon;
            break;
        case LIST_DOWN_MENU:
            selected_icon++;
            if (selected_icon > 3) selected_icon = 0; break;
        case LIST_UP_MENU:
            selected_icon--;
            if (selected_icon < 0) selected_icon = 3; break;
    }

    u8g2.setColorIndex(1);
    u8g2.drawRBox(0, 40, 128, 24,5);

    u8g2.setColorIndex(0); // Set color index to 1 before drawing the frames and text
    switch (selected_icon) {
        case 0:
            u8g2.setColorIndex(1);
            u8g2.drawRFrame(55, 12, 64, 12, 1); break;
        case 1:
            u8g2.setColorIndex(1);
            u8g2.drawRFrame(55, 24, 64, 12, 1); break;

        case 2:
            u8g2.drawRFrame(3, 42, 122, 12, 4); break;
        case 3:
            u8g2.drawRFrame(3, 52, 122, 12, 4); break;
    }
    u8g2.setColorIndex(0); 
    u8g2.setFont(u8g2_font_NokiaSmallBold_tr);
    u8g2.setFontMode(1);
    u8g2.setCursor(10, 51);
    u8g2.print("Save changes && Exit");
    u8g2.setCursor(15, 62);
    u8g2.print("Cancel && Exit)");

    return user_choice;
}

#define HIDEN 1
#define VISIBLE 0
#define READ_ONLY 1
#define NOT_READ_ONLY 0

editable_atributes get_editable_attributes(FileProperties* file_properties){
    editable_atributes attributes = {false, false};
    if(file_properties->attributes == 0x02)
        attributes.visibility = VISIBLE;
    else attributes.visibility = HIDEN;

    if(file_properties->attributes == 0x01)
        attributes.read_only = READ_ONLY;
    else attributes.read_only = NOT_READ_ONLY;

    return attributes;
}


void draw_attributes(editable_atributes* attributes){
    u8g2.setColorIndex(1);

    
    u8g2.setFont(u8g2_font_NokiaSmallBold_tr);

    u8g2.setCursor(0,22);
    u8g2.print("Visibility:    ");
    //u8g2.drawLine(0,21,128,21);

    switch(attributes->visibility){
        case HIDEN:
            u8g2.print("Hidden"); break;
        case VISIBLE:
            u8g2.print("Visible"); break;
    }
    u8g2.setCursor(0,34);
    u8g2.print("Read only:    ");
    ///u8g2.drawLine(0,31,128,31);

    switch(attributes->read_only){
        case NOT_READ_ONLY:
            u8g2.print("No"); break;
        case READ_ONLY:
            u8g2.print("Yes"); break;
    }


}
void Display_edit_attributes(FileProperties* file_properties, char* file_name){
    static unsigned long timer_1 = 0;
    editable_atributes attributes = get_editable_attributes(file_properties);
    selected_user_choice user_choice = {false, 0};

    while(1){
        ESP.wdtDisable();
        unsigned long currentMillis = millis();
        int command = serial_command();

        if (currentMillis - timer_1 >= 5) {
            u8g2.clearBuffer();
            draw_directory_info("File properties/Actions/Edit attributes");
            draw_attributes(&attributes);
            user_choice = draw_edit_attrib_menu_user(command);
            if(user_choice.is_selected){
                if(user_choice.selected_option == 0)
                    attributes.visibility = !attributes.visibility;
                if(user_choice.selected_option == 1)
                    attributes.read_only = !attributes.read_only;
                if(user_choice.selected_option == 2){
                    save_attributes(file_properties->name, &attributes); 
                    break;
                }

                if(user_choice.selected_option == 3) break;
            }
            u8g2.sendBuffer();
            timer_1 = currentMillis;
        }
        
        ESP.wdtEnable(WDTO_8S);
    }
}





#endif