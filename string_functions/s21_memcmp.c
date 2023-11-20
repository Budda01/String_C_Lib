#include "s21_string.h"


// int main() {
//     char str1[] = "hellohellohello";
//     char str2[] = "";
    
//     if (s21_memcmp(str1, str2, 20) == 0) {
//         printf("The two strings are identical\n");
//     } else {
//         printf("The two strings are different\n");
//     }
//     printf("%d\n", memcmp(str1, str2, 20));
//     printf("%d\n", s21_memcmp(str1, str2, 20));
    
//     return 0;

// }


int s21_memcmp(const void *str1, const void *str2, s21_size_t n){
    int check = 0;
    const unsigned char* st1 = (const unsigned char*)str1;
    const unsigned char* st2 = (const unsigned char*)str2;
    while (n > 0 && check < 1){
        if ((*st1 - *st2) != 0){
            check = 1;
        }
        st1++;
        st2++;
        n--;
    }
    st1--;
    st2--;
    return (*st1 - *st2);
}


