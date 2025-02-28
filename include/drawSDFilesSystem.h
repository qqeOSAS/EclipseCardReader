
// This file contains functions and logic for navigating and displaying file system 
// directories on a screen. It handles drawing directory contents, browsing files, 
// and interacting with different types of files such as text, image, and binary files.
// The primary function is DrawDirectoryStep(), which executes different steps for
// file handling, like clearing the display buffer, listing files, displaying file names,
// and processing user selection. The draw_directory() function periodically updates 
// the screen based on a timer to ensure smooth user interaction.

#ifndef DRAW_FILESYS
#define DRAW_FILESYS

#include <BinImageBrowser.h>
#include <XBMImagebrowser.h>
#include <txtFilesbrowser.h>
#include <BMPImageBrowser.h>
#include <drawFileMenu.h>
#include <File properties browser/draw_Properties.h>


bool DrawDirectoryStep(char* directory);
void draw_directory();

bool DrawDirectoryStep(char* directory){
    switch (drawState.step) {
        case 0:  // Очистка буфера
            u8g2.clearBuffer();
            u8g2.setColorIndex(1);
            drawState.step++;
            break;

        case 1:  // Getting files list
            drawState.fileCount = Files_list(directory, drawState.availableFiles);
            drawState.step++;
            break;

        case 2:  // Drawing selecting file icon
            drawState.result = draw_selecting_icon(1);
            drawState.step++;
            break;

        case 3:  // drawing file names      
            if(strcmp(directory,lastDirectory) != 0){
                drawState.reset_page = true;
                Serial.println("new DIR");
            }
            else
                drawState.reset_page = false;
            strcpy(lastDirectory,directory);
            drawState.pageNum = draw_file_names(drawState.availableFiles, drawState.fileCount, drawState.result.status,drawState.reset_page);
            drawState.step++;
            break;

        case 4:  // Directory info
            draw_directory_info(directory);
            drawState.step++;
            break;

        case 5:  // Processing file selecting
            drawState.selectedFileData = return_select_label(drawState.availableFiles, drawState.result.command, drawState.result.y, drawState.pageNum);
            if (drawState.selectedFileData.isSelected) {
                char newDirectory[100];

                if (isDirectory(directory)) {
                    Serial.print("Opening file: ");
                    Serial.println(directory);
                    snprintf(newDirectory, sizeof(newDirectory), "%s/%s", directory, drawState.selectedFileData.fileName);
                    strcpy(directory, newDirectory);
                    normalizePath(directory);
                    Serial.print("Entering directory: ");
                    Serial.println(directory);
                }
                
                if(isTextFile(directory))
                    browse_txt_file(directory);

                if(isXBMFile(directory))
                    browse_XBM_image(directory);

                //if(isHEADER_File(directory))
                   // browse_Header_image(directory);
                if(isBinFile(directory))
                    browse_bin_image(directory);
                    
                if(isBMPfile(directory))
                    browse_BMP_image(directory);
                    
                
                
            }
            if(drawState.selectedFileData.openProperties ){
                //if(!isDirectory(drawState.selectedFileData.fileName))
                    draw_file_properties(drawState.selectedFileData.fileName);
            }

            if (drawState.result.command == BACK) {
                getParentDirectory(directory);
                drawState.step = 0; 
                return false;      
            }

            drawState.step++;
            break;
        case 6: 
        Serial.print("ФАЙЛ:");
        Serial.print(drawState.selectedFileData.openProperties); // Send draw buffer to display
            u8g2.sendBuffer();
            drawState.step = 0; 
            return false;     
    }

    yield(); 
    return true; 
}

void draw_directory(){
    static unsigned long timer_1 = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - timer_1 >= 5) { 
        if (!DrawDirectoryStep(currentDirectory)) {
            timer_1 = currentMillis;
        }
    }

    yield(); 

}

void displaySDFileSystem(){
///////////////костиль!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(!begin_SD()){
        bool begin_sd_b = false;
        while(!begin_sd_b){
            ESP.wdtDisable();
            static unsigned long timer_1  = 0;
            unsigned long curt_millis = millis();

            if(curt_millis - timer_1 >= 2000){
                begin_sd_b = begin_SD();
                timer_1 = curt_millis;
            }

            draw_insert_SD_screen();
            ESP.wdtEnable(WDTO_8S);
        }
    }

    if(begin_SD()){
        while(1){
            listDown_btn.tick();
            if(listDown_btn.isHold())
                break;
            ESP.wdtDisable();
            draw_directory();
            ESP.wdtEnable(WDTO_8S);
        }
    }

}




#endif