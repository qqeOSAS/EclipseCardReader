#ifndef BITMAPS
#define BITMAPS

#include <Arduino.h>



const unsigned char player_stop_icon_bitmap [] PROGMEM = {
	0xfe, 0x0f, 0x03, 0x18, 0xfb, 0x1b, 0xfb, 0x1b, 0xfb, 0x1b, 0xfb, 0x1b, 0x03, 0x18, 0xfe, 0x0f
};
const unsigned char player_play_icon_bitmap [] PROGMEM = {
	0xfe, 0x0f, 0x47, 0x1c, 0x47, 0x1c, 0x47, 0x1c, 0x47, 0x1c, 0x47, 0x1c, 0x47, 0x1c, 0xfe, 0x0f
};
const unsigned char move_frames_left_icon_bitmap [] PROGMEM = {
	0xfe, 0x0f, 0xdf, 0x1b, 0xe7, 0x1c, 0x31, 0x1e, 0x18, 0x1f, 0x63, 0x1c, 0xdf, 0x1b, 0xfe, 0x0f
};
const unsigned char move_frames_right_icon_bitmap [] PROGMEM = {
	0xfe, 0x0f, 0x7b, 0x1f, 0xe7, 0x1c, 0x8f, 0x11, 0x1f, 0x03, 0xc7, 0x18, 0x7b, 0x1f, 0xfe, 0x0f
};
const unsigned char palyer_backgroung_image [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

const unsigned char main_screen_frames_bitmap_128x64 [] PROGMEM = {
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char folder_icon_10x8 [] PROGMEM = {
	0x3e, 0x00, 0x42, 0x00, 0xff, 0x03, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02, 0xfe, 0x01
};
const unsigned char txt_file_icon_10x8 [] PROGMEM = {
	0xfe, 0x00, 0x01, 0x01, 0x3d, 0x02, 0x01, 0x02, 0x7d, 0x02, 0x01, 0x02, 0xfd, 0x02, 0xfe, 0x01
};
const unsigned char XBM_file_icon_10x8 [] PROGMEM = {
	0xff, 0x01, 0x09, 0x02, 0x09, 0x02, 0x0f, 0x02, 0x01, 0x02, 0xff, 0x03, 0x55, 0x03, 0xfe, 0x01
};
const unsigned char BIN_file_icon_10x8 [] PROGMEM = {
	0x10, 0x00, 0x47, 0x02, 0xd5, 0x02, 0xd5, 0x02, 0x57, 0x03, 0x55, 0x03, 0x55, 0x02, 0x57, 0x02
};
const unsigned char WiFI_waves_icon10x8 [] PROGMEM = {
	0x00, 0x00, 0xfe, 0x01, 0xff, 0x03, 0x01, 0x02, 0xfc, 0x00, 0x84, 0x00, 0x30, 0x00, 0x30, 0x00
};

// 'Wifi deather icon', 10x8px
const unsigned char epd_bitmap_Wifi_deather_icon [] PROGMEM = {
	0xfe, 0x01, 0xff, 0x03, 0x31, 0x02, 0x31, 0x02, 0xcf, 0x03, 0xfe, 0x01, 0xb6, 0x01, 0xb6, 0x01
};
// 'WiFI jammer', 10x8px
const unsigned char epd_bitmap_WiFI_jammer [] PROGMEM = {
	0xfc, 0x00, 0xb6, 0x01, 0x03, 0x03, 0x49, 0x02, 0x79, 0x02, 0x03, 0x03, 0xb6, 0x01, 0xfc, 0x00
};
// 'Disconnect from wifi', 10x8px
const unsigned char epd_bitmap_Disconnect_from_wifi [] PROGMEM = {
	0xfe, 0x01, 0x81, 0x03, 0x81, 0x03, 0xe1, 0x02, 0x79, 0x02, 0x1f, 0x02, 0x07, 0x02, 0xfe, 0x01
};
// 'connect to wifi icon', 10x8px
const unsigned char epd_bitmap_connect_to_wifi_icon [] PROGMEM = {
	0xfc, 0x00, 0x02, 0x01, 0x78, 0x00, 0x84, 0x00, 0x30, 0x00, 0x00, 0x00, 0xfc, 0x00, 0xfe, 0x01
};
// 'ESP_NOW ICON', 10x8px
const unsigned char epd_bitmap_ESP_NOW_ICON [] PROGMEM = {
	0x02, 0x01, 0x49, 0x02, 0x85, 0x02, 0xb5, 0x02, 0xb5, 0x02, 0x85, 0x02, 0x49, 0x02, 0x02, 0x01
};

const unsigned char* WiFi_options_icons[6] = {
	epd_bitmap_connect_to_wifi_icon,
	epd_bitmap_Disconnect_from_wifi,
	epd_bitmap_ESP_NOW_ICON,
	epd_bitmap_WiFI_jammer,
	epd_bitmap_Wifi_deather_icon,
	epd_bitmap_ESP_NOW_ICON

};
// 'Rename file icon', 10x8px
const unsigned char epd_bitmap_Rename_file_icon [] PROGMEM = {
	0xc0, 0x02, 0x40, 0x01, 0xa0, 0x02, 0x50, 0x03, 0xb0, 0x00, 0x70, 0x00, 0x0c, 0x00, 0xfe, 0x01
};
// 'Delete file icon', 10x8px
const unsigned char epd_bitmap_Delete_file_icon [] PROGMEM = {
	0x3e, 0x00, 0x42, 0x00, 0xff, 0x03, 0x49, 0x02, 0x31, 0x02, 0x31, 0x02, 0x49, 0x02, 0xfe, 0x01
};
// 'edit attrib icon', 10x8px
const unsigned char epd_bitmap_edit_attrib_icon [] PROGMEM = {
	0x32, 0x01, 0x7b, 0x03, 0x86, 0x01, 0x33, 0x03, 0x33, 0x03, 0x86, 0x01, 0x7b, 0x03, 0x32, 0x01
};

const unsigned char* file_actions_icons[4] = {
	epd_bitmap_Delete_file_icon,
	epd_bitmap_edit_attrib_icon,
	epd_bitmap_Rename_file_icon,
	BIN_file_icon_10x8
};

const unsigned char enter_char_panel [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x53, 0x03, 0xa4, 0x54, 0x01, 0x84, 
	0x54, 0x01, 0xbc, 0x57, 0x03, 0xa0, 0x54, 0x01, 0xbc, 0x24, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbc, 0xd4, 0x07, 0x84, 0x04, 0x01, 
	0x04, 0x13, 0x01, 0x1c, 0x13, 0x01, 0x84, 0x14, 0x01, 0xbc, 0x14, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x01, 0x10, 0x09, 
	0x01, 0x08, 0x06, 0x01, 0x08, 0x06, 0x01, 0x10, 0x09, 0x01, 0xe0, 0xff, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};
// '1 point', 15x14px
const unsigned char epd_bitmap_1_point [] PROGMEM = {
	0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 
	0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0x3f, 0x7e, 0x1f, 0x7c, 0x3f, 0x7e
};
// '2 point', 15x14px
const unsigned char epd_bitmap_2_point [] PROGMEM = {
	0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0x1f, 0x7c, 
	0x0f, 0x78, 0xc7, 0x71, 0xe7, 0x73, 0x3f, 0x7e, 0x1f, 0x7c, 0x3f, 0x7e
};
// 'Connected no internet', 15x14px
const unsigned char epd_bitmap_Connected_no_internet [] PROGMEM = {
	0x03, 0x0c, 0x01, 0x2c, 0x00, 0x2e, 0xfc, 0x2f, 0x06, 0x2c, 0x03, 0x2e, 0xf1, 0x2f, 0x19, 0x2c, 
	0x0f, 0x2e, 0xc7, 0x5f, 0xe7, 0x7f, 0x3f, 0x0e, 0x1f, 0x2c, 0x3f, 0x0e
};
// '3 point', 15x14px
const unsigned char epd_bitmap_3_point [] PROGMEM = {
	0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0x07, 0x70, 0x03, 0x60, 0xf1, 0x47, 0x19, 0x4c, 
	0x0f, 0x78, 0xc7, 0x71, 0xe7, 0x73, 0x3f, 0x7e, 0x1f, 0x7c, 0x3f, 0x7e
};
// 'Full pover', 15x14px
const unsigned char epd_bitmap_Full_pover [] PROGMEM = {
	0x03, 0x60, 0x01, 0x40, 0x00, 0x00, 0xfc, 0x1f, 0x06, 0x30, 0x03, 0x60, 0xf1, 0x47, 0x19, 0x4c, 
	0x0f, 0x78, 0xc7, 0x71, 0xe7, 0x73, 0x3f, 0x7e, 0x1f, 0x7c, 0x3f, 0x7e
};
// 'Not connected', 15x14px
const unsigned char epd_bitmap_Not_connected [] PROGMEM = {
	0x1f, 0x7c, 0xc7, 0x61, 0xf3, 0x43, 0xf9, 0x49, 0xfc, 0x24, 0x7e, 0x32, 0x3e, 0x39, 0x9e, 0x3c, 
	0x4e, 0x3e, 0x26, 0x1f, 0x91, 0x4f, 0xc3, 0x63, 0xe7, 0x70, 0x1f, 0x7c
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 288)
const int epd_bitmap_allArray_LEN = 6;
const unsigned char* connected_WiFi_pover_icons[6] = {
	epd_bitmap_1_point,
	epd_bitmap_2_point,
	epd_bitmap_3_point,
	epd_bitmap_Full_pover,
	
};

const unsigned char epd_bitmap_Eclipse_logo_65x15 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xe1, 0x0f, 0x0f, 0x07, 0x1f, 0x78, 
	0xfe, 0x00, 0x06, 0x31, 0x18, 0x0d, 0xc5, 0x30, 0x4e, 0x83, 0x00, 0xfa, 0xd9, 0x37, 0x0d, 0x45, 
	0x67, 0x62, 0xfd, 0x00, 0x1a, 0x6c, 0x6c, 0x0d, 0x65, 0x49, 0x59, 0x0d, 0x00, 0x1a, 0x34, 0x48, 
	0x0d, 0x65, 0x59, 0x19, 0x0d, 0x00, 0xfa, 0x15, 0x78, 0x0d, 0x65, 0x5d, 0x33, 0xfd, 0x00, 0x02, 
	0x15, 0x00, 0x0d, 0x65, 0x65, 0x22, 0x81, 0x00, 0xfa, 0x15, 0x78, 0x0d, 0x65, 0x35, 0x4e, 0xfd, 
	0x00, 0x1a, 0x34, 0x48, 0x0d, 0x65, 0x1d, 0x4c, 0x0d, 0x00, 0x1a, 0x6c, 0x6c, 0x7d, 0x65, 0x81, 
	0x4c, 0x0d, 0x00, 0xfa, 0xd9, 0x37, 0x4d, 0x25, 0x81, 0x23, 0xfd, 0x00, 0x06, 0x31, 0x18, 0x41, 
	0x25, 0x81, 0x38, 0x83, 0x00, 0xfc, 0xe1, 0x0f, 0x7f, 0xe7, 0x81, 0x0f, 0xfe, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char epd_bitmap_cardreaded_logo_60x13 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x60, 0xcf, 0x67, 0x3c, 0xdf, 0x03, 
	0x26, 0x00, 0x60, 0xdb, 0x61, 0x6c, 0xc7, 0x06, 0x26, 0xe7, 0x78, 0xdb, 0xf1, 0x6c, 0xc7, 0x06, 
	0xa6, 0x6d, 0x6d, 0xdb, 0xf1, 0x6c, 0xc7, 0x06, 0x86, 0x6d, 0x6d, 0xcf, 0xb7, 0x6c, 0xdf, 0x03, 
	0x06, 0x6c, 0x6d, 0xdb, 0x91, 0x6c, 0xc7, 0x06, 0x26, 0x6f, 0x6c, 0xdb, 0x91, 0x6c, 0xc7, 0x06, 
	0xa6, 0x6d, 0x6c, 0xdb, 0xf1, 0x6c, 0xc7, 0x06, 0xa6, 0x6d, 0x6c, 0xdb, 0x91, 0x6c, 0xc7, 0x06, 
	0xa6, 0x6d, 0x6c, 0xdb, 0x91, 0x6c, 0xc7, 0x06, 0x3c, 0x6f, 0x78, 0xdb, 0x97, 0x3c, 0xdf, 0x06, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'Icon 0-25%', 20x20px
const unsigned char epd_bitmap_Icon_0_25_ [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x38, 0xc5, 0x01, 0x28, 0x47, 0x01, 0x38, 
	0xc0, 0x01, 0x00, 0x00, 0x00, 0x80, 0x0f, 0x00, 0xc0, 0x98, 0x03, 0x5c, 0x90, 0x02, 0x54, 0x90, 
	0x03, 0x5c, 0x10, 0x00, 0xc0, 0x18, 0x00, 0x80, 0x0f, 0x00, 0x38, 0xc0, 0x01, 0x28, 0x40, 0x01, 
	0x38, 0xc7, 0x01, 0x00, 0x05, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00
};
// 'pixels 25-50%', 20x20px
const unsigned char epd_bitmap_pixels_25_50_ [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x04, 0x05, 0x01, 0x18, 0xc7, 0x00, 0x28, 
	0xa0, 0x00, 0x30, 0x60, 0x00, 0x80, 0x0f, 0x00, 0xc0, 0x1b, 0x00, 0xd8, 0xd3, 0x00, 0xd6, 0x53, 
	0x03, 0xd8, 0xd1, 0x00, 0xc0, 0x19, 0x00, 0x80, 0x0f, 0x00, 0x30, 0x60, 0x00, 0x28, 0xa0, 0x00, 
	0x18, 0xc7, 0x00, 0x04, 0x05, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
};
// 'pixels 50-75%', 20x20px
const unsigned char epd_bitmap_pixels_50_75_ [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x04, 0x07, 0x01, 0x18, 0xc7, 0x00, 0x38, 
	0xe0, 0x00, 0x30, 0x60, 0x00, 0x80, 0x0f, 0x00, 0xc0, 0x1f, 0x00, 0xd8, 0xdf, 0x00, 0xde, 0xdf, 
	0x03, 0xd8, 0xdf, 0x00, 0xc0, 0x1f, 0x00, 0x80, 0x0f, 0x00, 0x30, 0x60, 0x00, 0x38, 0xe0, 0x00, 
	0x18, 0xc7, 0x00, 0x04, 0x07, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
};
// '75-100%', 20x20px
const unsigned char epd_bitmap_75_100_ [] PROGMEM = {
	0x00, 0x02, 0x08, 0x01, 0x07, 0x06, 0x06, 0x07, 0x07, 0x0e, 0x87, 0x03, 0x1c, 0xc7, 0x01, 0x38, 
	0xe0, 0x00, 0x30, 0x60, 0x00, 0x80, 0x0f, 0x00, 0xd0, 0x1f, 0x00, 0xde, 0xdf, 0x03, 0xdf, 0xdf, 
	0x07, 0xde, 0xdf, 0x03, 0xd0, 0x1f, 0x00, 0x80, 0x0f, 0x00, 0x30, 0x60, 0x00, 0x38, 0xe0, 0x00, 
	0x1c, 0xc7, 0x01, 0x0e, 0x87, 0x03, 0x06, 0x07, 0x03, 0x01, 0x02, 0x04
};



const unsigned char* epd_bitmap_brightness_icons_20X20[4] = {
	epd_bitmap_Icon_0_25_,
	epd_bitmap_pixels_25_50_,
	epd_bitmap_pixels_50_75_,
	epd_bitmap_75_100_
};







#endif