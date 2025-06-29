#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  const unsigned char *st = (const unsigned char *)src;
  s21_size_t len = s21_strlen(dest);
  s21_size_t len2 = s21_strlen(src);
  if (n > len2) {
    n = len2;
  }
  s21_size_t counter = n;
  dest += len;
  while (n > 0) {
    *dest = *st;
    dest++;
    st++;
    n--;
  }
  return (void *)dest - len - counter;
}