#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *copy = S21_NULL;
  int start_count = 0;
  int end_count = s21_strlen(src) - 1;
  if (src != S21_NULL && trim_chars != S21_NULL) {
    while (s21_strchr(trim_chars, src[start_count]) != S21_NULL &&
           src[start_count] != '\0') {
      start_count++;
    }
    while (s21_strchr(trim_chars, src[end_count]) != S21_NULL &&
           end_count > start_count) {
      end_count--;
    }
    s21_size_t copy_len = (end_count - start_count) + 1;
    copy = (char *)calloc(copy_len, sizeof(char));
    for (s21_size_t i = 0; i <= copy_len; i++) {
      copy[i] = src[i + start_count];
    }
    copy[copy_len] = '\0';
  } else if (trim_chars == S21_NULL) {
    s21_size_t len_src = s21_strlen(src) + 1;
    copy = (char *)calloc(len_src, sizeof(char));
    for (s21_size_t i = 0; i < len_src; i++) {
      copy[i] = src[i];
    }
  }
  return copy;
}