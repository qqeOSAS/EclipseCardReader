#ifndef BINARY_READ
#define BINARY_READ

#include <SDCardConfig.h>
bool isBinFile(const char* filepath){
        const char* ext = strrchr(filepath, '.'); 
    if (ext) {
        if (strcasecmp(ext, ".bin") == 0) 
            return true;
    }
    return false;
}
void print_binary_image(uint8_t* binImage) {
    Serial.println("Displaying first 64 bytes of the image buffer:");
    
    // Виводимо перші 64 байти з зображення
    for (int i = 0; i < 64; i++) {
        if (i % 16 == 0) {
            Serial.println();  // Додаємо новий рядок після кожних 16 байтів
        }
        Serial.print(binImage[i], HEX);  // Виводимо байт у шістнадцятковому форматі
        Serial.print(" ");
    }
    Serial.println();  // Додаємо ще один новий рядок в кінці
}


Draw_Image read_binary_image(const char* filename,int page) {

    SdFile bin_file;
    Draw_Image binImage = {0, 0, {0}};  

    unsigned long startTime = micros();

    int position = (page - 1) *1024;

    if (!bin_file.open(filename, O_READ)) { 
        return binImage;  
    }
    uint32_t fileSize = bin_file.fileSize();
    binImage.image_pages = fileSize / 1024;
    Serial.println(startTime);

    int index = 0;
    bin_file.seekSet(position); 
    

    while (bin_file.available() && index < 1024) {
        int bytes_read = bin_file.read(&binImage.image_buffer[index], sizeof(binImage.image_buffer) - index);
        index += bytes_read;
        
        if (index >= sizeof(binImage.image_buffer)) {
            break;  
        }
        yield();
    }
    bin_file.close();
    unsigned long endTime = micros();
    long duration = (endTime - startTime) / 1000;

    Serial.print("BIN READ END");
    Serial.println(endTime);

    Serial.print("Read Duration");
    Serial.print(duration);
    Serial.println("MS");
      // Закриваємо файл після завершення
    //print_binary_image(binImage.image_buffer);

    return binImage; 
}



#endif