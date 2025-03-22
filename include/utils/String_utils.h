#ifndef STRING_UTILS
#define STRING_UTILS


#include <stdio.h>
#include <string.h>



void add_char(char *str, char c, int max_size) {
    int len = strlen(str);
    if (len < max_size - 1) {  // Перевіряємо, чи є місце
        str[len] = c;
        str[len + 1] = '\0'; // Завжди закінчуємо `\0`
    }
}







#endif