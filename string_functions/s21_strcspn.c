#include "s21_string.h"

// int main(){
//     char str[] = "Hello, world";
//     char charset[] = "l";
//     int length = strcspn(str, charset);
//     printf("Length of initial segment without vowels: %d\n", length);
//     return 0;
// }

s21_size_t s21_strcspn(const char *str1, const char *str2){
    int check = 0;
    s21_size_t count = 0;
    int len1 = s21_strlen(str1);
    int len2 = s21_strlen(str2);
    for(int i = 0; i < len1; i++){
        for(int j = 0; j < len2; j++){
            if (str1[i] != str2[j] && check == 0){
                count++;
            }
            else
                check = 1;
        }
    }
    return count;
}

