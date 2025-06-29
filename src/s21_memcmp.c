#include "s21_string.h"

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  int check = 0;
  const unsigned char* st1 = (const unsigned char*)str1;
  const unsigned char* st2 = (const unsigned char*)str2;
  while (n > 0 && check < 1) {
    if ((*st1 - *st2) != 0) {
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
