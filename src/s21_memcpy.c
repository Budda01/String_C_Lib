#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  const unsigned char *source = (const unsigned char *)src;
  unsigned char *des = (unsigned char *)dest;
  while (n > 0) {
    *des++ = *source++;
    n--;
  }
  return dest;
}