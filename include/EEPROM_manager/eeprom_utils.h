#ifndef EEPROM_SAVE_H
#define EEPROM_SAVE_H

#include "EEPROM_config.h"
#include  <Arduino.h>


template<typename T>
bool eeprom_save_struct(int address, const T& data) {
    eeprom_begin();
    EEPROM.put(address, data);
    bool ok = EEPROM.commit();
    eeprom_end();
    return ok;
}
template<typename T>
bool eeprom_load_struct(int address, T& data) {
    eeprom_begin();
    EEPROM.get(address, data);
    EEPROM.end();
    return true;
}
void eeprom_clear() {
    eeprom_begin();
    for (int i = 0; i < EEPROM_SIZE; i++) {
        EEPROM.write(i, 0);
    }
    EEPROM.commit();
    eeprom_end();
}
void eeprom_print() {
    eeprom_begin();
    for (int i = 0; i < EEPROM_SIZE; i++) {
        ESP.wdtDisable();
        Serial.print("Address ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(EEPROM.read(i));
        ESP.wdtEnable(WDTO_8S);
    }
    eeprom_end();
}
void load_EEPROM_data(){
    eeprom_load_struct(DISPLAY_SETTINGS_EEPROM_ADDRESS, display_settings_eeprom);
}




#endif // EEPROM_SAVE_H