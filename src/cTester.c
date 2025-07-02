#include <stdio.h>
#include <string.h>

char* read_token(char* str, const char* delim) {
    // Використовуємо strtok для отримання токена
    char* token = strtok(str, delim);
    if (token != NULL) {
        printf("Current token: %s\n", token);
    }
    return token;
}

int main() {
    char ssids[] = "Manyuk_log";

    char *token;

    // Отримуємо перший токен
    token = read_token(ssids, "_");

    // Цикл для отримання наступних токенів
    while (token != NULL) {
        token = read_token(NULL, "_");
    }

    return 0;
}