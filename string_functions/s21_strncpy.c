#include "s21_string.h"


int main() {
    char destination[20];
    char source[20] = "Hello again";
    s21_strncpy(destination, source, 13);
    printf("Destination: %s\n", destination);
    return 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n){
    int i = 0;
    while (n > 0){
        dest[i] = src[i];
        i++;
        n--;
    }
    return dest;
}