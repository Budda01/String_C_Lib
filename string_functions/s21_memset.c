#include "s21_string.h"



// int main() {
//     char str[] = "This is a test string";
//     char new_str[20];

//     // Копируем первые 10 символов из str в new_str
//     s21_memset(new_str, 'e', sizeof(new_str)); // Заполняем new_str нулями
//     memcpy(new_str, str, 10);

//     // Выводим содержимое new_str
//     printf("Содержимое new_str: %s\n", new_str);

//     return 0;
// }


void *s21_memset(void *str, int c, s21_size_t n){
    unsigned char* st = (unsigned char*)str;
    while (n > 0){
    *st = c; 
    st++;
    n--;
    }
    return st;
}