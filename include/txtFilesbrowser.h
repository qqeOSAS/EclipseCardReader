#ifndef TXT_FILE_BROWSER
#define TXT_FILE_BROWSER



#include <drawtxtfile.h>
#include <ReadTxt.h>

void browse_txt_file(char* directory);


void browse_txt_file(char* directory){
    int page = 0;
    readTextFile(directory,page);
    while(drawState.result.command != BACK){
        ESP.wdtDisable();
        bool read_next_page = false;
        switch(drawState.result.command){
            case LIST_DOWN_MENU:
                page++;
                read_next_page = true;
                break;
            case LIST_UP_MENU:
                page--;
                read_next_page = true;
                if(page < 0)
                    page = 0;
                break;
        }
        if(read_next_page){
            readTextFile(directory,page);
            read_next_page = false;
        }

        draw_text_file(directory,text_file_page_buffer);


        ESP.wdtEnable(WDTO_8S);
    }
    for (int i = 0; i < sizeof(text_file_page_buffer); i++) {
        text_file_page_buffer[i] = '\0';
    }




}




#endif