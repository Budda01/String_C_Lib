#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int check = 0;
  s21_size_t count = 0;
  int len1 = s21_strlen(str1);
  int len2 = s21_strlen(str2);
  for (int i = 0; i < len1; i++) {
    if (check != 1) {
      for (int j = 0; j < len2; j++) {
        if (str1[i] == str2[j]) check = 1;
      }
      if (check != 1) count++;
    }
  }
  return count;
}
