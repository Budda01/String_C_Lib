#include "s21_string.h"

// int main() {
//     char str1[] = "Hello world";
//     char str2[] = "world";

//     char *ptr = s21_strstr(str1, str2);

//     if (ptr != NULL) {
//         printf("Substring found at index: %ld\n", ptr - str1);
//     } else {
//         printf("Substring not found in str1\n");
//     }

//     return 0;
// }


char *s21_strstr(const char *haystack, const char *needle){
    int check = 0;
    int i = 0;
    int count = 0;
    int len_ned = s21_strlen(needle);
    while (*haystack != '\0' && check == 0){
        while(*haystack == needle[i] && i < len_ned){
            haystack++;
            count++;
            i++;
        }
        if (count == len_ned){
            check = 1;
            haystack -= len_ned;
        }
        else{
            haystack -= count;
            i = 0;
            count = 0;
        }
        haystack++;
    }
    return check == 1 ? (char*)(haystack-1): S21_NULL;
}