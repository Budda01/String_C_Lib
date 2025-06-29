#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *copy = S21_NULL;
  if (str) {
    int len = s21_strlen(str) + 1;
    copy = (char *)calloc(len, sizeof(char));
    for (int i = 0; i <= len; i++) {
      if (str[i] >= 97 && str[i] <= 122)
        copy[i] = (str[i] - 32);
      else
        copy[i] = str[i];
    }
  }
  return copy;
}