// ФАйл відкриття текстових файлів та перегляду їх вмісту




#ifndef TXT_FILE_BROWSER
#define TXT_FILE_BROWSER

#include <drawtxtfile.h>
#include <ReadTxt.h>

// Function to browse a text file
void browse_txt_file(char* directory) {
    char* text_file_page_buffer = (char*)malloc(131); // 130 bytes plus the string terminator

    if (text_file_page_buffer == NULL)
        return;


    uint32_t page = 0; // current page number, 
    uint32_t file_pages = readTextFile(directory, page, text_file_page_buffer, 131);
    if (file_pages < 0) {
        free(text_file_page_buffer);
        return;
    }

    // Loop to handle txt file braowsing
    while (1) {

        ESP.wdtDisable();  
        uint8_t command = serial_command();  // Get the user command from the serial input
        bool read_next_page = false; 

        // Handle user commands
        switch (command) {
            case BACK:
                getParentDirectory(directory);  
                free(text_file_page_buffer);  
                return;  
            case LIST_DOWN_MENU: // move to the next page
                if (page + 1 >= file_pages) {
                    break;
                }
                page++;
                read_next_page = true;  // Set the flag to read the next page
                break;
            case LIST_UP_MENU: 
                if (page == 0) {
                    break;
                }
                page--;
                read_next_page = true;
                break;
        }

        // Read the next page of the text file if the flag is set
        if (read_next_page) {
            readTextFile(directory, page,text_file_page_buffer, 131);  // Read the text file at the current page
            read_next_page = false;  
        }

        draw_text_file(directory,text_file_page_buffer);  // Display the text file on the screen

        ESP.wdtEnable(WDTO_8S);  
    }

}

#endif
////sukagit 