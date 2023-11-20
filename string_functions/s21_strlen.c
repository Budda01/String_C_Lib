#include "s21_string.h"


// int main() {
//     char str[] = "Hello, friend!";
//     int length = s21_strlen(str);
//     int length2 = strlen(str);
//     printf("%d\n%d\n", length, length2);
//     printf("%c", str[length2]);
//     return 0;
// }

s21_size_t s21_strlen(const char *str){
    s21_size_t len = 0;
    const char* st = (const char*)str;
    while (*st != '\0'){
        len++;
        st++;
    }
    return(len);
}