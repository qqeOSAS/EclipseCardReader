
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







void draw_directory_new(char* directory){
    while(1){
        ESP.wdtDisable();
        u8g2.clearBuffer();
        u8g2.setColorIndex(1);

        drawState.fileCount = Files_list(directory, drawState.availableFiles);

        drawState.result = draw_selecting_icon(1);

        if(strcmp(directory,lastDirectory) != 0){
            drawState.reset_page = true;
            Serial.println("new DIR");
        }
        else
            drawState.reset_page = false;
    
        strcpy(lastDirectory,directory);
        drawState.pageNum = draw_file_names(drawState.availableFiles, drawState.fileCount, drawState.result.status,drawState.reset_page,1,1,0,0);
        draw_directory_info(directory);

        drawState.selectedFileData = return_select_label(drawState.availableFiles, drawState.result.command, drawState.result.y, drawState.pageNum);

        if (drawState.selectedFileData.isSelected) {

            char* newDirectory = (char*)malloc(300);

            if (isDirectory(directory)) {
                Serial.print("Opening file: ");
                Serial.println(directory);
                snprintf(newDirectory, 300, "%s/%s", directory, drawState.selectedFileData.fileName);
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

            free(newDirectory);
        }
        
        if(drawState.selectedFileData.openProperties ){
            //if(!isDirectory(drawState.selectedFileData.fileName))
            snprintf(Properties_directory, sizeof(Properties_directory), "%s/%s", directory, drawState.selectedFileData.fileName);
            draw_file_properties(Properties_directory);
        }

 
        u8g2.sendBuffer();
        if (drawState.result.command == BACK && strcmp(directory, "/") == 0) {
            //getParentDirectory(directory);
            break ;      
        }
        if (drawState.result.command == BACK){
            getParentDirectory(directory);
        }
    
    
        ESP.wdtEnable(WDTO_8S);
    }
}


void displaySDFileSystem(){
///////////////костиль!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(!begin_SD()){
        bool begin_sd_b = false;
        unsigned long start_time = millis();
        unsigned long end_time = start_time + 10000;
        while(!begin_sd_b){
            ESP.wdtDisable();
            start_time = millis();
            static unsigned long timer_1  = 0;
            unsigned long curt_millis = millis();

            if(start_time >= end_time){
                break;
            }

            if(curt_millis - timer_1 >= 2000){
                begin_sd_b = begin_SD();
                timer_1 = curt_millis;
            }
            if(listDown_btn.isHold())
            break;

            draw_insert_SD_screen();
            ESP.wdtEnable(WDTO_8S);
        }
    }


    draw_directory_new(currentDirectory);

}




#endif