#ifndef doom_melt_h
#define doom_melt_h

#include <Arduino.h>
#include <DisplayConfig.h>
#include <SdCard_utils.h>

#define WIDTH 128
#define HEIGHT 64
#define BYTES_PER_COL (HEIGHT / 8)  // 8
void split_xbm_into_columns(const uint8_t *xbm, uint8_t *columns, int width, int height) {
    for (int x = 0; x < width; x++) {
        for (int y_byte = 0; y_byte < height / 8; y_byte++) {
            uint8_t value = 0;
            for (int bit = 0; bit < 8; bit++) {
                int y = y_byte * 8 + bit;
                if (y >= height) break;

                int byte_index = (y * ((width + 7) / 8)) + (x / 8);
                uint8_t byte = xbm[byte_index];

                if (byte & (1 << (x % 8))) {
                    value |= (1 << bit);
                }
            }
            columns[x * (height / 8) + y_byte] = value;
        }
    }
}

void draw_byte_pixels(uint8_t byte, int x, int y) {
    for (int bit = 0; bit < 8; bit++) {
        if (byte & (1 << bit)) {
            u8g2.drawPixel(x, y + bit);
        }
    }
}
void draw_column(int x, uint8_t* column) {
    for (int byte = 0; byte < 8; byte++) {
        draw_byte_pixels(column[byte], x, byte * 8);
    }
}
void draw_columns(uint8_t* columns) {
	for (int x = 0; x < 128; x++) {
		//draw_column(x, columns + x * 8);
        draw_column(x, columns + x * BYTES_PER_COL);
	}

}
void copy_column(uint8_t* dest, const uint8_t* src, int x) {
    for (int byte = 0; byte < BYTES_PER_COL; byte++) 
        dest[x * BYTES_PER_COL + byte] = src[x * BYTES_PER_COL + byte];
    
}
void copy_columns(uint8_t* dest,uint8_t* src){
    for(byte x = 0; x < 128; x++) copy_column(dest, src, x);
}
uint8_t* melt_delay;

uint8_t* melt_order;

void generate_doom_style_delays() {
    const uint8_t max_delay = 15;
    const uint8_t group_size = 4;  // по 4 колонки в групі
    for (int x = 0; x < 128; x += group_size) {
        uint8_t delay = random(0, max_delay + 1);  // для всієї групи
        for (int i = 0; i < group_size && x + i < 128; i++)
            melt_delay[x + i] = delay;
        
    }

    // Легке перемішування сусідніх груп, щоби не було занадто рівно
    for (int i = 0; i < 10; i++) {
        int a = random(0, 127);
        int b = random(0, 127);
        uint8_t t = melt_delay[a];
        melt_delay[a] = melt_delay[b];
        melt_delay[b] = t;
    }
}


// makes meltig effect for 1 column of image
// 1 column 8 bytes 64 bit
bool melt_column_bit(uint8_t* melt_column, uint8_t* new_column, uint8_t local_melt_step) {
    if (local_melt_step >= 64) return true;  // захист від виходу за межі

    uint8_t pixel_index = 63 - local_melt_step;  // pixel number in column
    uint8_t new_bit = (new_column[pixel_index / 8] >> (pixel_index % 8)) & 0x01;

    // Shifting all bytes of melt_column down by 1 bit + adding new bit
    for (int8_t byte = 7; byte >= 0; --byte) {
        uint8_t next_bit = (byte > 0) ? ((melt_column[byte - 1] & 0x80) >> 7) : new_bit;
        melt_column[byte] = (melt_column[byte] << 1) | next_bit;
    }
    // Перевірка чи колонка зсунулась до кінця і дорівнює new_column
    for (uint8_t n = 0; n < BYTES_PER_COL; ++n) {
        if (melt_column[n] != new_column[n]) 
            return false;
    }
    return true;
}

bool melt_columns(uint8_t* melt_columns, uint8_t* new_columns, uint8_t step) {
    bool all_melt_finished = true;
    for (byte x = 0; x < 128; x++) {
		
        if (step >= melt_delay[x]) {
            uint8_t local_step = step - melt_delay[x];
            uint8_t* calculeted_melt_column = melt_columns + x * BYTES_PER_COL;
            uint8_t* calculated_new_column = new_columns + x * BYTES_PER_COL;

            bool column_melt_finished = melt_column_bit(calculeted_melt_column,calculated_new_column,local_step);
            if (!column_melt_finished) all_melt_finished = false;
        }
        else 
            all_melt_finished = false;  
    }
    return all_melt_finished;
}
void print_columns(uint8_t* columns) {
    for (int x = 0; x < 128; x++) {
        Serial.print("Column ");
        Serial.print(x);
        Serial.print(": ");
        for (int byte = 0; byte < 8; byte++) {
            if (columns[x * 8 + byte] < 16) Serial.print("0");
            Serial.print(columns[x * 8 + byte], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }
}

void doom_melt_frame_change(const uint8_t* old_image, const uint8_t* new_image) {
    uint8_t* old_image_columns = (uint8_t*)malloc(128 * 8);
    uint8_t* new_image_columns = (uint8_t*)malloc(128 * 8);
    uint8_t* melt_columns_buf = (uint8_t*)malloc(128 * 8);
    melt_delay = (uint8_t*)malloc(128);
    melt_order = (uint8_t*)malloc(128);

    if (!old_image_columns || !new_image_columns || !melt_columns_buf) return;
    
    split_xbm_into_columns(new_image, new_image_columns, 128, 64);
    split_xbm_into_columns(old_image, old_image_columns, 128, 64);
    copy_columns(melt_columns_buf, old_image_columns);

    byte step = 0;
   	bool melt_finished = false;
   	generate_doom_style_delays();
    while (!melt_finished) {
        ESP.wdtDisable();
        melt_finished = melt_columns(melt_columns_buf, new_image_columns, step);
        u8g2.clearBuffer();
        draw_columns(melt_columns_buf);
        u8g2.sendBuffer();
		if(melt_finished)
			delay(100);
        ESP.wdtEnable(WDTO_8S);
        step++;
    }
    free(old_image_columns);
    free(new_image_columns);
    free(melt_columns_buf);
    free(melt_delay);
    free(melt_order);
}
void draw_doom_frame_change(){
    uint_8t_xbm_image eclipse_logo = {0,0, nullptr};
    uint_8t_xbm_image next_frame_image = {0,0, nullptr};
    screenshoot_path next_frame_filepath = {NULL};
    screenshoot_path screenshot_filepath = process_screenshot();
    draw_main_screen(&next_frame_filepath,1);

    if (screenshot_filepath.full_filepath != NULL && next_frame_filepath.full_filepath != NULL) {
        eclipse_logo = extract_XBM_uint8_t(screenshot_filepath.full_filepath);
        next_frame_image = extract_XBM_uint8_t(next_frame_filepath.full_filepath);
        delete_sd_file(screenshot_filepath.full_filepath);
        delete_sd_file(next_frame_filepath.full_filepath);
                
        free(screenshot_filepath.full_filepath); // Звільняємо пам'ять після використання
        free(next_frame_filepath.full_filepath);

        doom_melt_frame_change(eclipse_logo.image_buffer, next_frame_image.image_buffer);
        free(eclipse_logo.image_buffer);
        free(next_frame_image.image_buffer);
            
    }
}


#endif