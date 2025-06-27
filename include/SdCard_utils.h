#ifndef SD_UTILS
#define SD_UTILS

#include <SDCardConfig.h>
#include <SdFat.h>
#include <SdFatConfig.h>
#include <DisplayConfig.h>

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
//1
    if (!file.open(path)) 
        return false;  // Якщо шлях не існує, повертаємо false
    
    bool isDir = file.isDir();  // Перевіряємо, чи це директорія
    file.close();
    return isDir;
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

    byte file_count = 0;


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
    if(sd.exists(directory))
        return false; // Якщо папка вже існує, повертаємо false
    if (sd.mkdir(directory)) {
        Serial.print("Папка успішно створена: ");
        Serial.println(directory);
        return true;
    } 
    else {
        Serial.print("Помилка при створенні папки: ");
        Serial.println(directory);
        return false;
    }
 
}
bool create_txt_file(const char* filepath, char* filename, char* content) {
    begin_SD();
    SdFile file;

    size_t full_filepath_size = strlen(filepath) + strlen(filename) + 2 + 4; // +1 for '/', +4 for ".txt"
    char* full_filepath = (char*)malloc(full_filepath_size);

    if (full_filepath == NULL) {
        return false; 
    }
    snprintf(full_filepath, full_filepath_size, "%s/%s.txt", filepath, filename);

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
bool create_bin_file(const char* filepath, char* filename, uint8_t* content_data, long content_size){
    begin_SD();
    SdFile file;

    size_t full_filepath_size = strlen(filepath) + strlen(filename) + 2 + 4; // +1 for '/', +4 for ".bin"
    char* full_filepath = (char*)malloc(full_filepath_size);

    if (full_filepath == NULL) return false; 
    snprintf(full_filepath, full_filepath_size, "%s/%s.bin", filepath, filename);

    if(file.exists(full_filepath)) {
        Serial.println("File already exists!");
        free(full_filepath);  // Не забувайте звільнити пам'ять
        return false;
    }
    // creating bin file
    if (file.open(full_filepath, O_CREAT | O_WRITE)) {

       for (long i = 0; i < content_size; i++) 
            file.write(content_data[i]); // Записуємо дані в файл по одному байту
    
        file.write(content_data, content_size); // Записуємо весь буфер за один разu8g2
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
bool save_xbm_screenshot(const char* filepath, const char* filename) {
    begin_SD();
    SdFile file;

    size_t full_filepath_size = strlen(filepath) + strlen(filename) + 2 + 4; // +1 for '/', +4 for ".xbm"
    char* full_filepath = (char*)malloc(full_filepath_size);

    if (full_filepath == NULL) return false; 

    snprintf(full_filepath, full_filepath_size, "%s/%s.xbm", filepath, filename);

    if (file.exists(full_filepath)) {
        Serial.println("File already exists!");
        free(full_filepath);  // Не забувайте звільнити пам'ять
        return false;
    }

    // Створення файлу і запис у нього
    if (file.open(full_filepath, O_CREAT | O_WRITE)) {
        u8g2.writeBufferXBM(file); // Записуємо весь буфер за один раз
        file.close();
        Serial.println("Файл XBM успішно створено!");
        free(full_filepath);  // Звільнення пам'яті
        return true;
    } 
    else {
        Serial.println("Не вдалося створити файл XBM!");
        free(full_filepath);  // Звільнення пам'яті
        return false;
    }

}
struct uint_8t_xbm_image {
    uint16_t width;
    uint16_t height;
    uint8_t* image_buffer; // динамічний буфер
};

uint_8t_xbm_image extract_XBM_uint8_t(const char* filepath) {
    begin_SD(); 
    uint_8t_xbm_image uint8_t_Image = {0, 0, nullptr};
    SdFile XBM_file;
       if (!XBM_file.open(filepath, O_READ)) {
        Serial.print("Failed to open file: ");
		
        Serial.println(filepath);
        return uint8_t_Image; // Повертаємо порожню структуру
    }

    char line[128];
    // 1. Зчитуємо ширину та висоту
    while (XBM_file.available()) {
        XBM_file.fgets(line, sizeof(line));
        if (strncmp(line, "#define", 7) == 0) {
            if (strstr(line, "_width") != NULL) {
                char* number = strrchr(line, ' ');
                if (number != NULL) uint8_t_Image.width = atoi(number);
            } else if (strstr(line, "_height") != NULL) {
                char* number = strrchr(line, ' ');
                if (number != NULL) uint8_t_Image.height = atoi(number);
            }
        }
        if (uint8_t_Image.width && uint8_t_Image.height) break;
    }

    // 2. Розраховуємо розмір буфера
    size_t buf_size = ((uint8_t_Image.width + 7) / 8) * uint8_t_Image.height;
    uint8_t_Image.image_buffer = (uint8_t*)calloc(buf_size,1);

    if (!uint8_t_Image.image_buffer) {
        Serial.println("Не вдалося виділити пам'ять!");
        XBM_file.close();
        return uint8_t_Image;
    }

    // 3. Знаходимо початок масиву даних
    bool data_section = false;
    int byte_index = 0;
    XBM_file.seek(0); // rewind
    while (XBM_file.available()) {
        XBM_file.fgets(line, sizeof(line));
        if (!data_section && strchr(line, '{')) 
            data_section = true;
        
        if (data_section) {
            char* token = strtok(line, ", \n{}");
            while (token && byte_index < buf_size) {
                if (strstr(token, "0x")) {
                    uint8_t value = strtol(token, NULL, 16);
                    uint8_t_Image.image_buffer[byte_index++] = value;
                }
                token = strtok(NULL, ", \n{}");
            }
            if (strchr(line, '}')) break;
        }
    }
    XBM_file.close();
    
    return uint8_t_Image;
}
void print_uint8_array_chunks(const uint8_t* data, size_t size) {
    const size_t chunk_size = 1024;

    for (size_t i = 0; i < size; i += chunk_size) {
        size_t remaining = size - i;
        size_t current_chunk_size = remaining < chunk_size ? remaining : chunk_size;

        Serial.printf("---- Chunk %u (%u bytes) ----\n", i / chunk_size, current_chunk_size);
        for (size_t j = 0; j < current_chunk_size; ++j) {
            Serial.printf("0x%02X", data[i + j]);
            if (j < current_chunk_size - 1) Serial.print(", ");
            if ((j + 1) % 16 == 0) Serial.println();  // Новий рядок кожні 16 байтів
        }
        Serial.println("\n");
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