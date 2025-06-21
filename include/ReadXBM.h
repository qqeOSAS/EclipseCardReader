#ifndef READ_XBM
#define READ_XBM

#include <SDCardConfig.h>

Draw_Image read_XBM_image(const char* filename);

bool isXBMFile(const char* filepath);



Draw_Image read_XBM_image(const char* filename) {
    SdFile XBM_file;
    Draw_Image xbmImage = {0, 0, {0}}; 
    unsigned long startTime = micros();

    if (!XBM_file.open(filename, O_READ)) {
        Serial.print("Failed to open file: ");
		
        Serial.println(filename);
        return xbmImage; 
    }
    Serial.print("BIN READ START:");
    Serial.println(startTime);

    char line[128];
    int byte_index = 0;

    while (XBM_file.available()) {
        int len = XBM_file.fgets(line, sizeof(line)); 
        if (len == 0) {
            Serial.println("Error reading line.");
            break;
        }

       
        if (strncmp(line, "#define", 7) == 0) {
            if (strstr(line, "_width") != NULL) {
                char *number = strrchr(line, ' ');
                if (number != NULL) {
                    xbmImage.width = atoi(number);
                }
            } else if (strstr(line, "_height") != NULL) {
                char *number = strrchr(line, ' ');
                if (number != NULL) {
                    xbmImage.height = atoi(number);
                }
            }
            continue; 
        }

        
        if (byte_index < sizeof(xbmImage.image_buffer)) {
            char *token = strtok(line, ", \n");
            while (token != NULL && byte_index < sizeof(xbmImage.image_buffer)) {
                if (strstr(token, "0x") != NULL) {
                    uint8_t value = strtol(token, NULL, 16); 
                    xbmImage.image_buffer[byte_index++] = value;
                }
                token = strtok(NULL, ", \n");
            }
        }
    }

    XBM_file.close(); 
    unsigned long endTime = micros();
    long duration = (endTime - startTime) / 1000;

    Serial.print("BIN READ END");
    Serial.println(endTime);

    Serial.print("Read Duration");
    Serial.print(duration);
    Serial.println("MS");
    return xbmImage;
}


bool isXBMFile(const char* filepath){
    const char* ext = strrchr(filepath, '.'); 
    if (ext) {
        if (strcasecmp(ext, ".XBM") == 0) 
            return true;
    }
    return false;
}


#endif