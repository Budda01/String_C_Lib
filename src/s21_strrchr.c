#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  s21_size_t count = 0;
  s21_size_t pos = 0;
  int check = 0;
  const char *st = str;
  while (*st != '\0') {
    if (*st == (unsigned char)c) {
      pos = count;
      check = 1;
    }
    count++;
    st++;
  }
  if (c == '\0') {
    st = (str + s21_strlen(str));
    check = 1;
  } else
    st = str + pos;
  return (check != 0) ? (char *)st : S21_NULL;
}
