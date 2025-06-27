#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H
#include  <EEPROM.h>
#define EEPROM_SIZE 512 // Define the size of the EEPROM


struct Display_settings_EEPROM {
    int brightness = 1;
};
Display_settings_EEPROM display_settings_eeprom;
#define DISPLAY_SETTINGS_EEPROM_ADDRESS 0 // Address in EEPROM for display settings
inline void eeprom_begin() {
    EEPROM.begin(EEPROM_SIZE);
}

inline void eeprom_end() {
    EEPROM.end();
}











#endif