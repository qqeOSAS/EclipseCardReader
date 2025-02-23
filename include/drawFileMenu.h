#ifndef DRAW_FILE_MENU
#define DRAW_FILE_MENU
#include <Arduino.h>
#include <DisplayConfig.h>
#include <SdCard_utils.h>
#include <UserInputs.h>

CommandData draw_selecting_icon(bool draw_icon);

SelectedFile return_select_label(char files_arr[][30], int command, int y, int page_num);

int draw_file_names(char files_arr[][30], int count, int status,bool reset_page);

void draw_directory_info(const char* directory);


CommandData draw_selecting_icon(bool draw_icon) {
    int command = serial_command();
    byte status = 0;
    static int x = 0;
    static int y = 12;

    switch (command) {
        case LIST_DOWN_MENU:
            y += 10;
            break;
        case LIST_UP_MENU:
            y -= 10;
            break;
        case SELECT:
            break;
    }

    if (y < 12) {
        y = 52;
        status = 1;
    } else if (y > 52) {
        y = 12;
        status = 2;
    }
    if(draw_icon)
        u8g2.drawFrame(x, y, 128, 10);

    return {status,command,y};
}

SelectedFile return_select_label(char files_arr[][30], int command, int y, int page_num) {
    #define PAGE_Y_0 12
    #define PAGE_Y_1 22
    #define PAGE_Y_2 32
    #define PAGE_Y_3 42
    #define PAGE_Y_4 52

    SelectedFile selectedFile;  

    int corrector = (page_num - 1) * 5;  
    selectedFile.isSelected = false;
    selectedFile.fileName[0] = '\0';  
    selectedFile.fileIndex = -1;

    if (command == SELECT) {
        selectedFile.isSelected = true; 
        
        switch (y) {
            case PAGE_Y_0:
                strcpy(selectedFile.fileName, files_arr[0 + corrector]);  
                selectedFile.fileIndex = 0 + corrector;
                break;
            case PAGE_Y_1:
                strcpy(selectedFile.fileName, files_arr[1 + corrector]);
                selectedFile.fileIndex = 1 + corrector;
                break;
            case PAGE_Y_2:
                strcpy(selectedFile.fileName, files_arr[2 + corrector]);
                selectedFile.fileIndex = 2 + corrector;
                break;
            case PAGE_Y_3:
                strcpy(selectedFile.fileName, files_arr[3 + corrector]);
                selectedFile.fileIndex = 3 + corrector;
                break;
            case PAGE_Y_4:
                strcpy(selectedFile.fileName, files_arr[4 + corrector]);
                selectedFile.fileIndex = 4 + corrector;
                break;
        }
    }

    Serial.print("Selected file: ");
    Serial.print(selectedFile.fileName);
    Serial.print(" at index: ");
    Serial.println(selectedFile.fileIndex);
    return selectedFile;
}

int draw_file_names(char files_arr[][30], int count, int status,bool reset_page) {
    u8g2.setFont(u8g2_font_5x8_t_cyrillic);

    const byte lines_per_page = 5;  
    const byte page_count = (count + lines_per_page - 1) / lines_per_page; 
    static byte page_num = 1; 
    int corrector = (page_num - 1) * lines_per_page; 

    if(reset_page){
        Serial.println("RESET_PAGE");
        page_num = 1;
        corrector = 0;
    }

    // updating page depending on the result
    if (status == 2 && page_num < page_count) {
        page_num++;
    } else if (status == 1 && page_num > 1) {
        page_num--;
    }
    // Updating corrector 
    byte x = 0;
    byte y = 20;
    Serial.print("Page: ");
    Serial.println(page_num);
    Serial.print("Corrector: ");
    Serial.println(corrector);  

    // Printing files names at current page on screen 
    for (int i = 0; i < lines_per_page; i++) {
        int file_index = corrector + i;
        if (file_index >= count) break; 

        u8g2.setCursor(x, y);
        u8g2.print(file_index + 1);  // file num
        u8g2.print(") ");
        u8g2.print(files_arr[file_index]);  // file name
        y += 10;
        Serial.print("File index: ");
        Serial.println(file_index);
        Serial.println(files_arr[file_index]);
    }
    return page_num;
}

//drawing information about SD size in root and current file path
void draw_directory_info(const char* directory){
    unsigned long currentTime = millis();
    static unsigned long timer_1 = 0;

    u8g2.setColorIndex(1);
    u8g2.drawBox(0,0,128,10);
    u8g2.setColorIndex(0);
    u8g2.setFontMode(1);
    //u8g2.setFont(u8g2_font_NokiaSmallBold_tr);   u8g2_font_6x13B_t_cyrillic u8g2_font_6x13_t_cyrillic
    u8g2.setFont(u8g2_font_6x13_t_cyrillic); 

    int directory_widht = u8g2.getUTF8Width(directory);

    static int x_pos = 0;
    u8g2.setCursor(x_pos,9);

    //sligting if path str longer then screen size
    if(directory_widht > 126){
        if(currentTime - timer_1 >= 10){
            x_pos -= 1;
            if(x_pos < -directory_widht - 30)
                x_pos = 130;
            timer_1 = currentTime;
        }
        
    }
    else
        x_pos = 0;

    u8g2.print(directory);


    if(strcmp(directory,"/") == 0){ // If root print sd details
        int SD_size = return_card_size();
        u8g2.print(" ");
        u8g2.print("SD Size:");
        u8g2.print(SD_size);
        u8g2.print("MB");
    }
    u8g2.setColorIndex(1);
}
void draw_insert_SD_screen(){
    u8g2.clearBuffer();

    u8g2.setColorIndex(1);
    u8g2.drawBox(0,0,128,10);
    u8g2.setColorIndex(0);
    u8g2.setFontMode(1);
    u8g2.setFont(u8g2_font_6x13_t_cyrillic);


    int str_widht = u8g2.getUTF8Width("/SD card not detected.Please insert Card");

    static int x_pos = 0;
    u8g2.setCursor(x_pos,9);

    //sligting if path str longer then screen size
    if(str_widht > 126){
        x_pos -= 1;
        if(x_pos < -str_widht - 30)
            x_pos = 130;
        
    }
    else
        x_pos = 0;

    u8g2.print("/SD card not detected.Please insert Card");


    u8g2.sendBuffer();
}


#endif