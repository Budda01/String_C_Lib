#include "s21_string.h"

s21_size_t s21_strlen(const char* str) {
  s21_size_t len = 0;
  const char* st = (const char*)str;
  while (st != S21_NULL && *st != '\0') {
    len++;
    st++;
  }
  return len;
}