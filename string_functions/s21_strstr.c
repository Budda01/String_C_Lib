#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  int check = 0;
  int i = 0;
  int count = 0;
  int len_ned = s21_strlen(needle);
  while (*haystack != '\0' && check == 0) {
    while (*haystack == needle[i] && i < len_ned) {
      haystack++;
      count++;
      i++;
    }
    if (count == len_ned) {
      check = 1;
      haystack -= len_ned;
    } else {
      haystack -= count;
      i = 0;
      count = 0;
    }
    haystack++;
  }
  return check == 1 ? (char *)(haystack - 1) : S21_NULL;
}