#include "s21_string.h"



// int main() {
//     char str[] = "This is a sample string";
//     char *ptr = s21_strchr(str, 'l'); // Finds the first occurrence of 's' in the string
//     if (ptr != NULL) {
//         printf("Found at position: %ld\n", ptr - str); // Calculates the position of the character
//     } else {
//         printf("Character not found\n");
//     }
//     return 0;
// }

char *s21_strchr(const char *str, int c){
    int check = 0;
    const char* st = str;
    while (*st != '\0' && check < 1){
        if (*st == c){
            check = 1;
        }
        st++;
    }
    if (check == 1)
        st--;
    return check == 1? (char*)st : S21_NULL;
}

