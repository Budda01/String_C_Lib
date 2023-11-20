#include "s21_string.h"

    
int main() {
    char src[] = "Hello, World!";
    char dest[20];

    // Копируем содержимое массива src в массив dest
    s21_memcpy(dest, src, 6);

    // Выводим содержимое массива dest
    printf("Содержимое массива dest: %s\n", dest);

    return 0;
}


void *s21_memcpy(void *dest, const void *src, s21_size_t n){
    const unsigned char* source = (const unsigned char*)src;
    unsigned char* des = (unsigned char*)dest;
    while (n > 0){
        *des = *source;
        des++;
        source++;
        n--;
    }
    return des;
}