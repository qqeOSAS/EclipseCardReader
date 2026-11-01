#ifndef TXT_FILE_BROWSER
#define TXT_FILE_BROWSER

#include <drawtxtfile.h>
#include <ReadTxt.h>

// Function to browse a text file
void browse_txt_file(char* directory);

void browse_txt_file(char* directory) {
    char* text_file_page_buffer = (char*)malloc(130);

    if(text_file_page_buffer == NULL)
        return;
    


    int page = 0;  // Initialize the page number to 1
    int file_pages  = readTextFile(directory, page,text_file_page_buffer);  // Read the first page of the text file

    // Loop to handle user commands
    while (1) {

        ESP.wdtDisable();  // Disable the watchdog timer
        uint8_t command = serial_command();  // Get the user command from the serial input

       
        bool read_next_page = false; 
        // Handle user commands
        switch (command) {
            case BACK:
                getParentDirectory(directory);  // Go back to the parent directory
                free(text_file_page_buffer);  // Free the memory allocated for the text file buffer
                return;  // Exit the function
            case LIST_DOWN_MENU:
                page++;
                if(page > file_pages){
                    page = page - 1;
                    break;
                }     // Move to the next page
                read_next_page = true;  // Set the flag to read the next page
                break;
            case LIST_UP_MENU:
                page--;  // Move to the previous page
                read_next_page = true;  // Set the flag to read the previous page
                if (page < 0)  // Ensure the page number is not less than 0
                    page = 0;
                break;
        }

        // If the flag is set, read the next page
        if (read_next_page) {
            readTextFile(directory, page,text_file_page_buffer);  // Read the text file at the current page
            read_next_page = false;  // Reset the flag
        }

        draw_text_file(directory,text_file_page_buffer);  // Display the text file on the screen

        ESP.wdtEnable(WDTO_8S);  // Enable the watchdog timer with an 8-second timeout
    }

}

#endif