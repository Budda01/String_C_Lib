#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *copy = S21_NULL;
  if (src && start_index <= s21_strlen(src)) {
    s21_size_t str_len = s21_strlen(str);
    s21_size_t src_len = s21_strlen(src);
    s21_size_t sum_len = src_len + str_len;
    copy = (char *)calloc(sum_len, sizeof(char));
    for (s21_size_t i = 0; i < start_index; i++) {
      copy[i] = src[i];
    }
    for (s21_size_t j = 0; j <= str_len; j++) {
      copy[j + start_index] = str[j];
    }
    for (s21_size_t k = start_index; k <= src_len; k++) {
      copy[k + str_len] = src[k];
    }
    copy[sum_len] = '\0';
  }
  return copy;
}