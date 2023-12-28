#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *copy = S21_NULL;
  if (str) {
    int len = s21_strlen(str);
    copy = (char *)calloc(len, sizeof(char));
    for (int i = 0; i <= len; i++) {
      if (str[i] >= 65 && str[i] <= 90)
        copy[i] = (str[i] + 32);
      else
        copy[i] = str[i];
    }
  }
  return copy;
}