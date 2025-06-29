#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int check = 0;
  const char *match = (const char *)str1;
  int len1 = s21_strlen(str1);
  int len2 = s21_strlen(str2);
  while (len1 > 0 && check == 0) {
    for (int i = 0; i < len2; i++) {
      if (*match == str2[i]) check = 1;
    }
    if (check == 0) {
      match++;
    }
    len1--;
  }
  return check == 1 ? (char *)match : S21_NULL;
}
