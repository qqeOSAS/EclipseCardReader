#ifndef RENAME_FILE
#define RENAME_FILE

#include <Arduino.h>
#include <DisplayConfig.h>
#include <drawFileMenu.h>
#include <WiFi Draw/draw_connect_toWiFi.h>

void Display_rename_file(char* old_filename){
    size_t old_fullpath_cpy_size = strlen(old_filename) + 1;
    char* old_fullpath_cpy = (char*)malloc(old_fullpath_cpy_size);
    strcpy(old_fullpath_cpy, old_filename);
    trimToLastDirectory(old_fullpath_cpy);

    strcpy(entered_str.entered_string, old_fullpath_cpy); // Очищаємо введений рядок
    free(old_fullpath_cpy);
    entered_str.isEntered = false;

    size_t str_size = strlen("Enter new filename") + 1; // +1 для '\0'
    char* str = (char*)malloc(str_size);
    if (str == NULL) {
        Serial.println("Failed to allocate memory for prompt");
        return; 
    }
    snprintf(str, str_size, "Enter new filename");
    while(1){
        ESP.wdtDisable();
        entered_str = draw_enter_string_screen(str);
        if (entered_str.isEntered){
            if(entered_str.selected_action == 2){
                strcpy(entered_str.entered_string, ""); // Очищаємо введений рядок
                entered_str.isEntered = false;
                entered_str.selected_action = 0;
                free(str);
                break;
            }
            if(entered_str.selected_action == 1){
                size_t old_filename_cpy_size = strlen(old_filename) + 1;
                char* old_filename_cpy = (char*)malloc(old_filename_cpy_size);
                strcpy(old_filename_cpy, old_filename);

                getParentDirectory(old_filename_cpy);

                size_t new_filename_size = strlen(entered_str.entered_string) + 1 + old_filename_cpy_size + 1;
                char* new_filename = (char*)malloc(new_filename_size);

                sprintf(new_filename, "%s/%s", old_filename_cpy, entered_str.entered_string);
                rename_sd_file(old_filename, new_filename);

                free(new_filename);
                free(old_filename_cpy);
                free(str);
                break;
            }

        }// Передаємо динамічно створений рядок





    }

    
}





#endif