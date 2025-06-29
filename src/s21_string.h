#ifndef S21_STRING
#define S21_STRING

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long s21_size_t;
#define S21_NULL ((void *)0)
#define MAX 16384

struct form {
  int c, d, f, s, u;
  int width;
  int precision;
  int lenght;
  int negative_number;
  int flags_check;
  int sharp;
  int space_count;
  int plus_count;
  int minus_count;
  int null_count;
};

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
char *s21_strerror(int errnum);
int isSep(char str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
int s21_sprintf(char *str, const char *format, ...);
int width_change(const char **sym, va_list *arguments);
int precision_change(const char **sym, va_list *arguments);
void flags_change(const char **sym, struct form *Formaters);
void get_specifier(const char **sym, struct form *Formaters);
void work_spec_d(char *buffer, struct form **Formaters, long int val);
void work_spec_f(char *buffer, struct form **Formaters, long double num);
void work_spec_u(char *buffer, struct form **Formaters, unsigned long int val);
void work_space(char *buffer, struct form *Formaters, va_list *arguments);
s21_size_t s21_pseudo_strcat(char *dest, char *src);
int int_convert_str(char *buffer, struct form **Formaters, long int val,
                    int check, int count_zeros, int count_val,
                    int val_for_zer_pres, int check_for_low_pres);
void value_creator(char *value_buffer, char *buffer, struct form Formaters);
void value_num_creator(char *value_buffer, char *buffer, struct form Formaters);
void value_str_creator(char *value_buffer, char *buffer, struct form Formaters);
void value_char_creator(char *value_buffer, char *buffer,
                        struct form Formaters);
int value_flags_check(char *value_buffer, struct form Formaters);
s21_size_t precision_print_nulls(char *value_buffer, char *buffer,
                                 struct form Formaters);
int value_width(char *value_buffer, char *buffer, struct form Formaters);
s21_size_t width_print_spaces(char *value_buffer, struct form Formaters,
                              s21_size_t diff_width);
s21_size_t writing_a_string(char *dest, char *src, int count);
void work_spec_c(char *buffer, va_list *arguments);
void work_spec_s(char *buffer, va_list *arguments);
int comparing(double val_for_low_pres, struct form **Formaters);
s21_size_t s21_pseudo_strcat(char *dest, char *src);

long int lenght_change_d(long int val, int lenghtType);
unsigned long int lenght_change_u(unsigned long int val, int lenghtType);
int lenght_check(const char **sym);

void get_specifier_scanf(const char **sym, struct form *Formaters);

int work_space_sscanf(char const **st, va_list *arguments, int count);
int s21_sscanf(char *str, const char *format, ...);

#endif  // S21_STRING