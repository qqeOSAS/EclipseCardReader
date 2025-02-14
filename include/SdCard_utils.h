#ifndef SD_UTILS
#define SD_UTILS

#include <SDCardConfig.h>

char lastDirectory[200] = "/";
char currentDirectory[200] = "/";
char text_file_page_buffer[130];


bool begin_SD();
void print_SD_info();
int return_card_size();
bool isDirectory(const char* path);
char global_derictory_files[MAX_GLOBAL_DERICTORY_FILES][30];

#define MAX_FILES 100  // Максимальна кількість файлів
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

    // Перевірка, чи існує шлях
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
    root.close(); // Закриваємо директорію

    // Якщо файлів немає
    return file_count; // Повертаємо кількість файлів
}



void copyToArray(char original[][30], int count, char destination[][30]) {
    for (int i = 0; i < count; i++) {
        strcpy(destination[i], original[i]); // Копіюємо рядок
    }
}

void getParentDirectory(char* currentDirectory) {
    char* lastSlash = strrchr(currentDirectory, '/');
    if (lastSlash != nullptr && lastSlash != currentDirectory) {
        *lastSlash = '\0'; // Видаляємо останній сегмент шляху
    } else {
        strcpy(currentDirectory, "/"); // Якщо це коренева директорія
    }
}

void normalizePath(char* path) {
    char* writePtr = path; // Позиція для запису
    char* readPtr = path;  // Позиція для читання
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
    *writePtr = '\0'; // Завершуємо рядок
}

bool isHEADER_File(const char* filepath){
    const char* ext = strrchr(filepath, '.'); 
    if (ext) {
        if (strcasecmp(ext, ".h") == 0) 
            return true;
    }
    return false;
}



#endif