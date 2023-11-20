#include "s21_string.h"


int main() {
    char destination[20] = "Hello, ";
    char source[] = "World!";
    strncat(destination, source, -3135); //При отрицательных значениях сига
    printf("%ld\n", s21_strlen(destination));
    printf("Concatenated string: %s\n", destination);
    return 0;
}


char *s21_strncat(char *dest, const char *src, s21_size_t n){
    const unsigned char* st = (const unsigned char*)src;
    s21_size_t len = s21_strlen(dest);
    if (n > len){
        n = len;
    }
    dest += len;
    while (n > 0){
        *dest = *st;
        dest++;
        st++; 
        n--;
    }
    return (void*)dest;
}