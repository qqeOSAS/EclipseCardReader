#ifndef SD_UTILS
#define SD_UTILS

#include <SDCardConfig.h>
#include <SdFat.h>
#include <SdFatConfig.h>

char lastDirectory[200] = "/";
char currentDirectory[200] = "/";
char text_file_page_buffer[130];
char Properties_directory[200];

bool begin_SD();
void print_SD_info();
int return_card_size();
bool isDirectory(const char* path);
char global_derictory_files[MAX_GLOBAL_DERICTORY_FILES][30];

#define MAX_FILES 1000  // Максимальна кількість файлів
#define DIRECTORY 1
#define TEXT_FILE 2
#define XBM_FILE 3

// Функція для отримання списку файлів у заданому каталозі

int Files_list(const char* directory, char files_arr[][30]);
void copyToArray(char original[][30], int count, char destination[][30]);
void getParentDirectory(char* currentDirectory);
void normalizePath(char* path);


bool begin_SD() {
     bool res;
     Serial.println("Cheking your card");

     // Ініціалізація SD-карти
     if (!sd.begin(SD_CS_PIN, SD_SCK_MHZ(10))) {
          Serial.println("SD card initialization EROR!");
          res = false;
     }
     else{
          Serial.println("SD-Card succsesfolly initalizated!!.");
          res = true;
     }
     return res;
}

void print_SD_info() {
     Serial.println("Info about your SD-CARD");
  

     Serial.print("Card Size: ");
     Serial.print(sd.card()->cardSize() / 2048); // Розмір у МБ
     Serial.println(" MB");

     Serial.print("File System: ");
     switch (sd.card()->type()) {
          case SD_CARD_TYPE_SD1:
               Serial.println("SD1");
               break;
          case SD_CARD_TYPE_SD2:
               Serial.println("SD2");
               break;
          case SD_CARD_TYPE_SDHC:
               Serial.println("SDHC");
               break;
          default:
               Serial.println("UNKNOWN");
     }
     
}
int return_card_size(){
     return sd.card()->cardSize() / 2048;
}
bool isDirectory(const char* path) {
    SdFile file;

    if (file.open(path)) {
        bool isDir = file.isDir();  // Перевіряємо, чи це директорія
        file.close();
        return isDir;
    } else {
        Serial.print("Failed to open path: ");
        Serial.println(path); // Виводимо шлях, який не вдалося відкрити
    }

    return false;  // Якщо шлях не існує або не є директорією
}


int Files_list(const char* directory, char files_arr[][30]) {
    SdFile root;
    SdFile file;
   
    
    // Відкриваємо вказану директорію
    if (!root.open(directory)) {
        Serial.print("Помилка відкриття директорії: ");
        Serial.println(directory);
        return 0;
    }

    int file_count = 0;


    // Читаємо файли в директорії
	Serial.print("Директорія:");
    Serial.println(directory); 
    while (file.openNext(&root, O_RDONLY)) {
        if (file_count >= MAX_FILES) {
            Serial.println("Досягнуто максимуму файлів.");
            file.close();
            break;
        }
        // Зберігаємо ім'я файлу
        if (file.isDir()) {
            file.getName(files_arr[file_count], 30);

        } 
          else {
            // Якщо це файл
               file.getName(files_arr[file_count], 30);
          }

        // Логування імені файлу 
          Serial.print("Файл: ");

        Serial.println(files_arr[file_count]);

        file_count++;
        file.close();
    }
    if (file_count == 0) {
        Serial.print("Файли не знайдені в директорії: ");
        Serial.println(directory);
    } 
    else {
        Serial.print("Знайдено файлів: ");
        Serial.println(file_count);
	}
    root.close(); 

    return file_count; 
}

void copyToArray(char original[][30], int count, char destination[][30]) {
    for (int i = 0; i < count; i++) {
        strcpy(destination[i], original[i]); 
    }
}

void getParentDirectory(char* currentDirectory) {
    char* lastSlash = strrchr(currentDirectory, '/');
    if (lastSlash != nullptr && lastSlash != currentDirectory) {
        *lastSlash = '\0'; 
    } else {
        strcpy(currentDirectory, "/"); 
    }
}


void normalizePath(char* path) {
    char* writePtr = path; 
    char* readPtr = path;  
    bool lastWasSlash = false;

    while (*readPtr != '\0') {
        if (*readPtr == '/') {
            if (!lastWasSlash) {
                *writePtr++ = *readPtr;
                lastWasSlash = true;
            }
        } else {
            *writePtr++ = *readPtr;
            lastWasSlash = false;
        }
        readPtr++;
    }
    *writePtr = '\0'; 
}

bool isHEADER_File(const char* filepath){
    const char* ext = strrchr(filepath, '.'); 
    if (ext) {
        if (strcasecmp(ext, ".h") == 0) 
            return true;
    }
    return false;
}

bool deleteFile(const char* filepath) {
    if (sd.remove(filepath)) {
        Serial.print("Файл успішно видалено: ");
        Serial.println(filepath);
        return true;
    } else {
        Serial.print("Не вдалося видалити файл: ");
        Serial.println(filepath);
        return false;
    }
}

struct FileProperties{
    unsigned long size;
    char name [11];
    uint8_t creation_time_day;
    uint8_t creation_time_month;
    uint16_t creation_time_year;
    uint8_t creation_time_hours;
    uint8_t creation_time_minutes;
    uint8_t creation_time_seconds;
    uint16_t lastWrite_date;
    uint16_t lastWrite_time;
    uint8_t attributes;

};


FileProperties get_file_properties(const char* filepath) {
    SdFile file;
    FileProperties properties = {0, "", 0, 0, 0, 0, 0, 0, 0, 0, 0};

    if (file.open(filepath, O_RDONLY)) {
        DirFat_t dir;
        file.dirEntry(&dir);
         // Отримання імені файлу
        strncpy(properties.name, (char*)dir.name, 11);
        properties.name[11] = '\0'; 
        

        uint16_t raw_creation_time = *reinterpret_cast<uint16_t*>(dir.createTime);
        uint16_t raw_creating_date = *reinterpret_cast<uint16_t*>(dir.createDate);

        // Перевіряємо, чи createDate існує, якщо ні - беремо modifyDate
        if (raw_creating_date == 0) {
            raw_creating_date = *reinterpret_cast<uint16_t*>(dir.modifyDate);
        }
        if (raw_creation_time == 0) {
            raw_creation_time = *reinterpret_cast<uint16_t*>(dir.modifyTime);
        }

        //printf("raw_creating_date = 0x%04X\n", raw_creating_date);
       // printf("raw_creation_time = 0x%04X\n", raw_creation_time);

        properties.creation_time_year = ((raw_creating_date >> 9) & 0x7F) + 1980;
        properties.creation_time_month = (raw_creating_date >> 5) & 0x0F;
        properties.creation_time_day = raw_creating_date & 0x1F;

        properties.creation_time_hours = (raw_creation_time >> 11) & 0x1F;
        properties.creation_time_minutes = (raw_creation_time >> 5) & 0x3F;
        properties.creation_time_seconds = (raw_creation_time & 0x1F) * 2;

        properties.lastWrite_date = *reinterpret_cast<uint16_t*>(dir.modifyDate);
        properties.lastWrite_time = *reinterpret_cast<uint16_t*>(dir.modifyTime);
        properties.attributes = dir.attributes;

        properties.size = file.fileSize();

        file.close();
    }
    return properties;
}
struct editable_atributes{
    bool visibility;
    bool read_only;
};
void save_attributes(const char* filepath, editable_atributes* attributes) {
    SdFile file;
    if (file.open(filepath, O_RDWR)) {
        DirFat_t dir;
        file.dirEntry(&dir);

        if (attributes->visibility)
            dir.attributes |= 0x02;
        else
            dir.attributes &= ~0x02;

        if (attributes->read_only)
            dir.attributes |= 0x01;
        else
            dir.attributes &= ~0x01;

        // Save the modified directory entry back to the file
        file.dirEntry(&dir);

        file.sync(); 
        file.close();
    } else {
        Serial.println("Не вдалося відкрити файл для запису.");
    }
}

bool delete_sd_file(const char* filepath) {
    if(!isDirectory(filepath)){
        if (sd.remove(filepath)) {
            Serial.print("Файл успішно видалено: ");
            Serial.println(filepath);
            return true;
        }
        else {
            Serial.println("Помилка при видаленні папки.");
            return false;
        }
    }
    //якщо пуста папка

    else{
        if(sd.rmdir(filepath)){
            Serial.println("Папка успішно видалена.");
            return true;
        } 
        else{ 
            Serial.println("Помилка при видаленні папки.");
            return false;
        }

    }
    
}
bool rename_sd_file(const char* old_filepath, const char* new_filepath) {
    if(sd.exists(old_filepath)){
        if(sd.rename(old_filepath, new_filepath)) {
            Serial.print("Файл успішно перейменовано: ");
            Serial.print(old_filepath);
            Serial.print(" -> ");
            Serial.println(new_filepath);
            return true;
        } 
        else {
            Serial.print("Помилка при перейменуванні файлу: ");
            Serial.print(old_filepath);
            Serial.print(" -> ");
            Serial.println(new_filepath);
            return false;
        }
    }
    return false;
}


#endif