#ifndef READ_SYSTEM_FILES
#define READ_SYSTEM_FILES

#include <SDCardConfig.h>
#include <SDCard_utils.h>
char* read_Wifi_log_file(const char* filefolder, char* filename) {
    SdFile file;

    size_t filepath_size = strlen(filefolder) + strlen(filename) + 2; // +1 для '\0' +1 для '/'
    char* full_filepath = (char*)malloc(filepath_size);

    if (!full_filepath) {
        return NULL;
    }
    sprintf(full_filepath, "%s/%s", filefolder, filename); // Формуємо коректний шлях

    Serial.print("Full file path: ");
    Serial.println(full_filepath);

    if (!sd.exists(full_filepath)) {
        free(full_filepath);
        return NULL;
    }

    if (!file.open(full_filepath, O_READ)) {
        Serial.print("Failed to open file: ");
        free(full_filepath);
        return NULL;
    }

    // Виділяємо буфер для читання файлу
    char* file_content = (char*)malloc(131); // 130 байт + 1 для '\0'
    if (!file_content) {
        file.close();
        free(full_filepath);
        return NULL;
    }

    byte array_index = 0;
    while (file.available() && array_index < 130) {
        int c = file.read();
        if (c != -1) { 
            file_content[array_index] = (char)c;
            array_index++;
        }
    }
    file_content[array_index] = '\0'; 

    file.close();
    free(full_filepath);

    // Шукаємо пароль
    char* start = strchr(file_content, '"'); 
    if (start) {
        char* end = strchr(start + 1, '"'); 
        if (end && (end > start + 1)) {
            size_t password_length = end - start - 1;
            if (password_length < 30) {
                char* password_buffer = (char*)malloc(password_length + 1);
                if (!password_buffer) {
                    free(file_content);
                    return NULL;
                }
                strncpy(password_buffer, start + 1, password_length);
                password_buffer[password_length] = '\0';
                Serial.print("Password found: ");
                Serial.println(password_buffer);
                free(file_content);
                return password_buffer;
            } 

        }
    }

    Serial.println("Password not found");
    free(file_content);
    return NULL;
}


#endif