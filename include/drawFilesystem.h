#ifndef DRAW_FILESYS
#define DRAW_FILESYS

#include <BinImageBrowser.h>
#include <XBMImagebrowser.h>
#include <txtFilesbrowser.h>
#include <BMPImageBrowser.h>


bool DrawDirectoryStep(char* directory);
void draw_directory();

bool DrawDirectoryStep(char* directory){
    switch (drawState.step) {
        case 0:  // Очистка буфера
            u8g2.clearBuffer();
            u8g2.setColorIndex(1);
            drawState.step++;
            break;

        case 1:  // Отримання списку файлів
            drawState.fileCount = Files_list(directory, drawState.availableFiles);
            drawState.step++;
            break;

        case 2:  // Відображення іконки вибору
            drawState.result = draw_selecting_icon(1);
            drawState.step++;
            break;

        case 3:  // Відображення імен файлів
            
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

        case 4:  // Інформація про директорію
            draw_directory_info(directory);
            drawState.step++;
            break;

        case 5:  // Обробка вибору файлу/каталогу
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

            if (drawState.result.command == BACK) {
                getParentDirectory(directory);
                drawState.step = 0; // Скидаємо стан для виходу
                return false;       // Вихід із функції
            }

            drawState.step++;
            break;

        case 6:  // Надсилання буфера
            u8g2.sendBuffer();
            drawState.step = 0; // Скидаємо стан після завершення
            return false;       // Вихід із функції
    }

    yield(); // Перерва для watchdog
    return true; // Продовження виконання
}

void draw_directory(){

    static unsigned long timer_1 = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - timer_1 >= 5) { // Частота оновлення
        if (!DrawDirectoryStep(currentDirectory)) {
            // Якщо всі кроки виконано, оновлення завершено
            timer_1 = currentMillis;
        }
    }

    yield(); // Забезпечує переривання для WDT

}




#endif