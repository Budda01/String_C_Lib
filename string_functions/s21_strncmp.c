#include "s21_string.h"

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  int diff = 0;
  int check = 0;
  const char* st1 = str1;
  const char* st2 = str2;
  if (st1 != S21_NULL && st2 != S21_NULL && n != 0) {
    while (n >= 1 && st1 && st2 && check == 0) {
      if ((*st1 - *st2) != 0) {
        diff = *st1 - *st2;
        check = 1;
      }
      st1++;
      st2++;
      n--;
    }
  } else
    diff = 0;

  return diff;
}
