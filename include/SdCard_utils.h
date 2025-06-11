#ifndef SD_UTILS
#define SD_UTILS

#include <SDCardConfig.h>
#include <SdFat.h>
#include <SdFatConfig.h>

char lastDirectory[200] = "/";
char currentDirectory[200] = "/";
//char text_file_page_buffer[130];
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
#define BIN_FILE 4

// Функція для отримання списку файлів у заданому каталозі

int Files_list(const char* directory, char files_arr[][30]);
void copyToArray(char original[][30], int count, char destination[][30]);
void getParentDirectory(char* currentDirectory);
void normalizePath(char* path);

bool begin_SD() {
    ESP.wdtDisable(); // Вимкнути watchdog timer, щоб уникнути перезавантаження під час ініціалізації SD
    Serial.println("Cheking your card");

 
    if (sd.begin(SD_CS_PIN, SD_SCK_MHZ(4))) {
        Serial.println("SD-Card successfully initialized!");
        ESP.wdtEnable(WDTO_8S);
        return true;
    }
    
    Serial.println("SD card initialization ERROR!");
    return false;
}


int return_card_size() {
    if (!sd.card()) return 0;
    uint64_t cardSize = sd.card()->sectorCount();
    if (!cardSize) return 0;
    // sectorCount() повертає кількість секторів по 512 байт
    // 1 МБ = 1024 * 1024 байт = 2048 * 512 байт
    return cardSize / 2048;
}
void print_SD_info() {
     Serial.println("Info about your SD-CARD");
  

     Serial.print("Card Size: ");
    int cardSize = return_card_size();
     Serial.print(cardSize);
     Serial.println(" MB");
    Serial.printf("Card Type: ");
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
void trimToLastDirectory(char* currentDirectory) {
    char* lastSlash = strrchr(currentDirectory, '/'); // Знаходимо останній слеш
    if (lastSlash != NULL) {
        // Зсуваємо рядок так, щоб залишити тільки частину після останнього слеша
        memmove(currentDirectory, lastSlash + 1, strlen(lastSlash));
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
        // Get file name
        file.getName(properties.name, sizeof(properties.name));
        properties.name[sizeof(properties.name) - 1] = '\0';

        // Get file size
        properties.size = file.fileSize();

        // Get last write date and time
        uint16_t date, time;
        if (file.getModifyDateTime(&date, &time)) {
            properties.lastWrite_date = date;
            properties.lastWrite_time = time;
        } else {
            properties.lastWrite_date = 0;
            properties.lastWrite_time = 0;
        }

        // Attributes are not directly accessible, set to 0 or implement if needed
        properties.attributes = 0;

        // Creation time is not available in standard SdFat, set to 0 or copy from modify time
        properties.creation_time_year = 0;
        properties.creation_time_month = 0;
        properties.creation_time_day = 0;
        properties.creation_time_hours = 0;
        properties.creation_time_minutes = 0;
        properties.creation_time_seconds = 0;

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
        // Direct modification of file attributes is not supported in standard SdFat.
        // This function is a placeholder and does not change file attributes.
        Serial.println("Зміна атрибутів файлу не підтримується стандартною бібліотекою SdFat.");
        file.close();
    } else {
        Serial.println("Не вдалося відкрити файл для запису.");
    }
}
// require full file path
bool delete_sd_file(const char* filepath) {
    begin_SD();
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
bool check_file_for_exist(const char* filepath){
    if(sd.exists(filepath)){
        return true;
    }
    return false;
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

bool create_directory(const char* directory) {
    begin_SD();
    if (!sd.exists(directory)) {
        if (sd.mkdir(directory)) {
            Serial.print("Папка успішно створена: ");
            Serial.println(directory);
            return true;
        } else {
            Serial.print("Помилка при створенні папки: ");
            Serial.println(directory);
            return false;
        }
    }
    else{
        Serial.print("Папка вже існує: ");
        Serial.println(directory);
        return false;
    }
    
    
}
bool create_txt_file(const char* filepath, char* filename, char* content) {
    begin_SD();
    SdFile file;

    size_t filepath_size = strlen(filepath) + strlen(filename) + 1;
    char* full_filepath = (char*)malloc(filepath_size);

    if (full_filepath == NULL) {
        return false; 
    }
    snprintf(full_filepath, filepath_size, "%s%s", filepath, filename);

    // Перевірка, чи файл вже існує
    if (file.exists(full_filepath)) {
        Serial.println("File already exists!");
        free(full_filepath);  // Не забувайте звільнити пам'ять
        return false;
    }

    // Створення файлу і запис у нього
    if (file.open(full_filepath, O_CREAT | O_WRITE)) {
        file.println(content);
        file.close();
        Serial.println("Файл успішно створено!");
        free(full_filepath);  // Звільнення пам'яті
        return true;
    } 
    else {
        Serial.println("Не вдалося створити файл!");
        free(full_filepath);  // Звільнення пам'яті
        return false;
    }
}

bool clear_txt_file(char* filepath){
    begin_SD();
    SdFile file;

    if (!file.open(filepath, O_RDWR))  {
        Serial.print("Не вдалося відкрити файл: ");
        Serial.println(filepath);
        return false;
    }
    
    if(!file.truncate(0)){
            Serial.println("Помилка при очищенні файлу!");
            file.close();
            return false;
     }

    Serial.println("Файл успішно очищено!");
    file.close();
    return true;    
}
void create_upload_file(SdFile &file,char* filepath){
    file.open(filepath, O_WRITE | O_CREAT | O_TRUNC);
    if (!file) {
        Serial.println("[UPLOAD] Failed to open file for writing!");
    }
}
void write_upload_file(SdFile &file, const uint8_t* buf, size_t size) {
    if (file) {
        file.write(buf, size);
        Serial.print("[UPLOAD] Writing chunk, size: ");
        Serial.println(size);
    } else {
        Serial.println("[UPLOAD] File not open for writing!");
    }
}



#endif