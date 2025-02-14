#ifndef DISPLAY_config
#define DISPLAY_config

#include <U8g2lib.h>




U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
void Begin_display(){
    u8g2.begin();
    u8g2.enableUTF8Print();
}

struct CommandData {
    byte status;
    int command;
    int y;
};
struct SelectedFile {
    bool isSelected;  // Чи був вибраний файл
    char fileName[30];  // Назва вибраного файлу
};
struct DrawState {
    int step = 0;         // Поточний крок
    int fileCount = 0;    // Кількість файлів у каталозі
    int pageNum = 0;      // Номер сторінки
    char availableFiles[100][30];
    bool reset_page = false;
    CommandData result;
    SelectedFile selectedFileData;
};
DrawState drawState;



#endif