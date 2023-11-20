#include "s21_string.h"


void *s21_memchr(const void *str, int c, s21_size_t n){
    int check = 0;
    const unsigned char* st;
    st = (const unsigned char*)str;
    while (n > 0 && check < 1){
        if (*st == (unsigned char)c){
            check = 1;
        }
        st++;
        n--;
    }
    if (check == 1)
        st--;
    return check == 1? (void*)st : S21_NULL;
}

