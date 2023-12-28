#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int check = 0;
  const char *st = str;
  while (*st != '\0' && check < 1) {
    if (*st == c) {
      check = 1;
    }
    st++;
  }
  if (check == 1) st--;
  return check == 1 ? (char *)st : S21_NULL;
}
