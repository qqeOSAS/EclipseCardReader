#ifndef DRAW_FILE_MENU
#define DRAW_FILE_MENU
#include <Arduino.h>
#include <DisplayConfig.h>
#include <SdCard_utils.h>
#include <UserInputs.h>
#include <Bitmaps_headers/Bitmaps.h>
#include <ReadTxt.h>
#include <ReadXBM.h>
#include <ReadBinary.h>
///sdsdsadadadasdasdasdasd
#define WIFI_ICONS 1



CommandData draw_selecting_icon(bool draw_icon);

SelectedFile return_select_label(char files_arr[][30], int command, int y, int page_num);


void draw_directory_info(const char* directory);
struct DrawOptionsState {
    int step = 0;         
    int OptionCount = 0;   
    int pageNum = 0;      
    bool reset_page = false;
    CommandData result;
    SelectedFile selectedFileData;
};
byte return_file_type_icon(char* filename){

    if(isTextFile(filename))
        return TEXT_FILE;
    if(isXBMFile(filename))
        return XBM_FILE;
    if(isBinFile(filename))
        return BIN_FILE;

    else 
        return DIRECTORY;

    return 0;
}
void draw_file_type_icon(byte y,byte file_type){
    switch(file_type){
        case DIRECTORY: u8g2.drawXBMP(2,y,10,8, folder_icon_10x8);  break;
        case TEXT_FILE: u8g2.drawXBMP(2,y,10,8,txt_file_icon_10x8); break;
        case XBM_FILE:  u8g2.drawXBMP(2,y,10,8,XBM_file_icon_10x8); break;
        case BIN_FILE:  u8g2.drawXBMP(2,y,10,8,BIN_file_icon_10x8); break;
    }
}
void draw_spec_icon(byte y, const unsigned char* bitmap){
    u8g2.drawXBMP(2,y,10,8,bitmap);
}

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
    if(command == OPEN_FILE_PROPERTIES){
        selectedFile.openProperties = true;
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

    return selectedFile;
}

int draw_file_names(char files_arr[][30], int count, int status, bool reset_page, bool draw_icons,bool skip_sim_icons, int8 draw_spec_similar_icons, const unsigned char* spec_individ_icons_arr[] = nullptr) {
    u8g2.setFont(u8g2_font_5x8_t_cyrillic);

    const byte lines_per_page = 5;  
    const byte page_count = (count + lines_per_page - 1) / lines_per_page; 
    static byte page_num = 1; 
    int corrector = (page_num - 1) * lines_per_page; 

    if (reset_page) {
        Serial.println("RESET_PAGE");
        page_num = 1;
        corrector = 0;
    }

    // updating page depending on the result
    if (status == 2 && page_num < page_count) 
        page_num++;
     
    else if (status == 1 && page_num > 1) 
        page_num--;
    

    byte y = 20;
    Serial.print("Page: ");
    Serial.println(page_num);
    Serial.print("Corrector: ");
    Serial.println(corrector);  

    // Printing file names at the current page on screen 
    for (int i = 0; i < lines_per_page; i++) {
        int file_index = corrector + i;
        if (file_index >= count) break;

        if(!skip_sim_icons && draw_icons){
            if (draw_spec_similar_icons == 1) 
                draw_spec_icon(y - 7, WiFI_waves_icon10x8);
        }

        if (skip_sim_icons && draw_icons) {
            if (spec_individ_icons_arr != nullptr)
                draw_spec_icon(y - 7, spec_individ_icons_arr[file_index]);
            else {
                byte file_type;
                if (draw_spec_similar_icons == 0) {
                        file_type = return_file_type_icon(files_arr[file_index]);
                        draw_file_type_icon(y - 7, file_type);
                }
            }
        }
        
        else if(!draw_icons) {
            u8g2.setCursor(0, y);
            u8g2.print(file_index);
            u8g2.print(")");
        }

        u8g2.setCursor(14, y);
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

    static int x_pos = 5;
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
        x_pos = 5;

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