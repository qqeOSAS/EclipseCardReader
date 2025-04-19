#ifndef STRING_UTILS
#define STRING_UTILS


#include <stdio.h>
#include <string.h>



void add_char_to_str(char *str, char c, int max_size) {
    int len = strlen(str);
    if (len < max_size - 1) {  
        str[len] = c;
        str[len + 1] = '\0'; 
    }
}
void remove_last_char(char *str) {
    int len = strlen(str);
    if (len > 0) {
        str[len - 1] = '\0'; 
    }
}
char* read_token(char* str, const char* delim) {
    // Використовуємо strtok для отримання токена
    char* token = strtok(str, delim);
    if (token != NULL) {
        printf("Current token: %s\n", token);
    }
    return token;
}







#endif