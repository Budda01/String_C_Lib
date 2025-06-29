#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  int check = 0;
  int count = 0;
  static char *start;

  if (str == NULL) {
    str = start;
  }

  while (*str != '\0' && check == 0) {
    if (isSep(*str, delim) == 1 && *(str - 1) != '\0') {
      check = 1;
      *str = '\0';
    }
    count++;
    str++;
  }

  if (count != 0) {
    start = str;
    str -= count;
  } else
    str = NULL;

  return (char *)str;
}

int isSep(char str, const char *delim) {
  int len = s21_strlen(delim);
  int check = 0;
  for (int i = 0; i < len; i++) {
    if (str == delim[i]) check = 1;
  }
  return check;
}