#include "s21_string.h"

// int main() {
//     char str1[] = "moooommmyyy!";
//     char str2[] = "m";

//     char *ptr = s21_strrchr(str1, str2[0]);

//     if (ptr != NULL) {
//         printf("First occurrence of a character from str2 in str1: %s\n", ptr);
//     } else {
//         printf("No character from str2 found in str1\n");
//     }

//     return 0;
// }

char *s21_strrchr(const char *str, int c){
    s21_size_t count = 0;
    s21_size_t pos = 0;
    const char* st = str;
    while (*st != '\0'){
        if (*st == (unsigned char)c){
            pos = count;
        }
        count++;
        st++;
    }
    if (c == '\0'){
        st = (str + s21_strlen(str));
        pos = 1;
    }
    else
        st = str + pos;
    return pos != 0 ? (char*)st : S21_NULL;
}


