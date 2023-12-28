#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  struct form Formaters = {0};
  char buffer[MAX];
  char value_buffer[MAX];
  va_list arguments;
  va_start(arguments, format);
  char *str_start = str;
  const char *sym = format;
  for (; *sym; sym++) {
    if (*sym != '%') {
      *str++ = *sym;
      continue;
    } else if (*sym == '%') {
      sym++;
      if (*sym == '%') {
        *str++ = *sym;
        continue;
      } else {
        s21_memset(&Formaters, 0, sizeof(Formaters));
      }
    }
    flags_change(&sym, &Formaters);
    Formaters.width = width_change(&sym, &arguments);
    Formaters.precision = precision_change(&sym, &arguments);
    Formaters.lenght = lenght_check(&sym);
    get_specifier(&sym, &Formaters);
    work_space(buffer, &Formaters, &arguments);
    value_creator(value_buffer, buffer, Formaters);
    str += s21_pseudo_strcat(str, value_buffer);
    s21_memset(buffer, 0, sizeof(buffer));
    s21_memset(value_buffer, 0, sizeof(value_buffer));
  }

  *str = '\0';
  va_end(arguments);
  return str - str_start;
}

void flags_change(const char **sym, struct form *Formaters) {
  while (**sym == ' ' || **sym == '+' || **sym == '-' || **sym == '0' ||
         **sym == '#') {
    Formaters->flags_check = 1;
    if (**sym == ' ') {
      Formaters->space_count = 1;
    } else if (**sym == '+') {
      Formaters->plus_count = 1;
    } else if (**sym == '-') {
      Formaters->minus_count = 1;
    } else if (**sym == '0') {
      Formaters->null_count = 1;
    } else if (**sym == '#') {
      Formaters->sharp = 1;
    }
    (*sym)++;
  }
}

int width_change(const char **sym, va_list *arguments) {
  int width = -1;
  if (**sym != '*' && **sym >= 48 && **sym <= 57) {
    int countd = 0;
    while (**sym >= 48 && **sym <= 57) {
      countd++;
      (*sym)++;
    }
    (*sym)--;
    int factor = 1;
    width = 0;
    for (int i = 0; i < countd; i++) {
      width += ((**sym % 48) * factor);
      factor *= 10;
      (*sym)--;
    }
    *sym += countd + 1;
  } else if (**sym == '*') {
    width = va_arg(*arguments, int);
    (*sym)++;
  }
  return width;
}

int precision_change(const char **sym, va_list *arguments) {
  int precision = -1;
  if (**sym == '.') {
    precision = 0;
    if (*++(*sym) != '*') {
      int countd = 0;
      while (**sym >= 48 && **sym <= 57) {
        countd++;
        (*sym)++;
      }
      (*sym)--;
      int factor = 1;
      precision = 0;
      for (int i = 0; i < countd; i++) {
        precision += ((**sym % 48) * factor);
        factor *= 10;
        (*sym)--;
      }
      *sym += countd + 1;
    } else {
      precision = va_arg(*arguments, int);
      (*sym)++;
    }
  }
  return precision;
}

void get_specifier(const char **sym, struct form *Formaters) {
  switch (**sym) {
    case 'c':
      Formaters->c = 1;
      break;
    case 'd':
      Formaters->d = 1;
      break;
    case 's':
      Formaters->s = 1;
      break;
    case 'f':
      Formaters->f = 1;
      break;
    case 'u':
      Formaters->u = 1;
      break;
    default:
      break;
  }
}

int int_convert_str(char *buffer, struct form **Formaters, long int val,
                    int check, int count_zeros, int count_val,
                    int val_for_zer_pres, int check_for_low_pres) {
  int count = 0;
  long int num;
  num = val;
  if (val_for_zer_pres >= 5 && (**Formaters).precision == 0) num++;
  if (check_for_low_pres == 1) num++;
  long int check_null = num, copy_num = num;
  if (copy_num > 0) {
    while (copy_num > 0) {
      copy_num /= 10;
      count++;
    }
  } else if (copy_num == 0)
    count = 1;
  char buff[count + 1];
  long int div;
  char ch;
  int i = 0;
  while (count > 0) {
    div = pow(10, (count - 1));
    ch = ((num / div) + 48);
    buff[i] = ch;
    num %= div;
    count--;
    i++;
  }
  buff[i] = '\0';
  if (check == 0 && check_null == 0 && (**Formaters).precision == 0) {
    if ((**Formaters).f == 1) {
      *buffer++ = buff[0];
      *buffer = '\0';
    } else
      *buffer = '\0';
  } else if (check == 1) {
    buffer += s21_strlen(buffer);
    if (count_val != 0) *buffer++ = '.';
    for (int j = 0; j < count_zeros; j++) *buffer++ = '0';
    for (int g = 0; g < count_val - count_zeros; g++) *buffer++ = buff[g];
    *buffer = '\0';
  } else if (check == 0) {
    for (s21_size_t i = 0; i <= s21_strlen(buff); i++) *buffer++ = buff[i];
    *buffer = '\0';
  }
  return 0;
}

void work_spec_d(char *buffer, struct form **Formaters, long int val) {
  if (val < 0) {
    (**Formaters).negative_number = 1;
    val = (-1) * val;
  }
  int_convert_str(buffer, Formaters, val, 0, 0, 0, 0, 0);
}

int comparing(double val_for_low_pres, struct form **Formaters) {
  int check = 0;
  int count = (**Formaters).precision;
  double val = val_for_low_pres + 0.00000000001;
  for (int i = 0; i < count; i++) {
    val = val * 10;
  }
  long int intPart = val;
  val -= intPart;
  if (roundl(val_for_low_pres) == 1 && roundl(val) == 1) check = 1;
  return check;
}

void work_spec_f(char *buffer, struct form **Formaters, long double num) {
  int check = 0;
  if (num < 0) {
    (**Formaters).negative_number = 1;
    num = (-1) * num;
  }
  long int intPart = (long int)num;
  int val_for_zer_pres = (num - intPart) * 10;
  double val_for_low_pres = (num - intPart);
  int check_for_low_pres = 0;
  if ((**Formaters).precision <= 3 && (**Formaters).precision > 0)
    check_for_low_pres = comparing(val_for_low_pres, Formaters);
  if (num >= intPart) {
    int_convert_str(buffer, Formaters, intPart, check, 0, 0, val_for_zer_pres,
                    check_for_low_pres);
    check = 1;
  }
  double next_val = num - intPart;
  int count;
  if ((**Formaters).precision == -1)
    count = 6;
  else
    count = (**Formaters).precision;
  if (check_for_low_pres == 1) next_val = 0.000000000000001;

  int count_zeros = 0;
  int check_zeros = 0;
  for (int i = 0; i < count; i++) {
    next_val *= 10;
    if ((int)next_val == 0 && check_zeros == 0)
      count_zeros++;
    else
      check_zeros = 1;
  }
  next_val = roundl(next_val);
  int_convert_str(buffer, Formaters, next_val, check, count_zeros, count, 0, 0);
}

void work_spec_u(char *buffer, struct form **Formaters, unsigned long int val) {
  int_convert_str(buffer, Formaters, val, 0, 0, 0, 0, 0);
}

void work_spec_c(char *buffer, va_list *arguments) {
  char val = va_arg(*arguments, int);
  *buffer++ = val;
  *buffer = '\0';
}

void work_spec_s(char *buffer, va_list *arguments) {
  char *val = va_arg(*arguments, char *);
  int count = s21_strlen(val);
  for (int i = 0; i < count; i++) {
    *buffer++ = *val++;
  }
  *buffer = '\0';
}

void work_space(char *buffer, struct form *Formaters, va_list *arguments) {
  if ((*Formaters).d == 1) {
    long int val = va_arg(*arguments, long int);
    val = lenght_change_d(val, Formaters->lenght);
    work_spec_d(buffer, &Formaters, val);
  } else if ((*Formaters).u == 1) {
    unsigned long int val = va_arg(*arguments, unsigned long int);
    val = lenght_change_u(val, Formaters->lenght);
    work_spec_u(buffer, &Formaters, val);
  } else if ((*Formaters).f == 1) {
    double val = va_arg(*arguments, double);
    work_spec_f(buffer, &Formaters, val);
  } else if ((*Formaters).c == 1) {
    work_spec_c(buffer, arguments);
  } else if ((*Formaters).s == 1) {
    work_spec_s(buffer, arguments);
  }
}

void value_creator(char *value_buffer, char *buffer, struct form Formaters) {
  if (Formaters.d == 1 || Formaters.f == 1 || Formaters.u == 1)
    value_num_creator(value_buffer, buffer, Formaters);
  else if (Formaters.s == 1) {
    if (Formaters.width != 0)
      value_str_creator(value_buffer, buffer, Formaters);
  } else if (Formaters.c == 1) {
    if (Formaters.precision == -1)
      value_char_creator(value_buffer, buffer, Formaters);
  }
}

void value_num_creator(char *value_buffer, char *buffer,
                       struct form Formaters) {
  if ((int)s21_strlen(buffer) >= Formaters.width &&
      (int)s21_strlen(buffer) >= Formaters.precision) {
    value_buffer += value_flags_check(value_buffer, Formaters);
    value_buffer += s21_pseudo_strcat(value_buffer, buffer);
  } else if ((int)s21_strlen(buffer) >= Formaters.width &&
             (int)s21_strlen(buffer) < Formaters.precision) {
    value_buffer += value_flags_check(value_buffer, Formaters);
    value_buffer += precision_print_nulls(value_buffer, buffer, Formaters);
    value_buffer += s21_pseudo_strcat(value_buffer, buffer);
  } else if ((int)s21_strlen(buffer) < Formaters.width &&
             (int)s21_strlen(buffer) >= Formaters.precision) {
    value_buffer += value_width(value_buffer, buffer, Formaters);
  } else if ((int)s21_strlen(buffer) < Formaters.width &&
             (int)s21_strlen(buffer) < Formaters.precision) {
    if (Formaters.precision > Formaters.width) {
      value_buffer += value_flags_check(value_buffer, Formaters);
      value_buffer += precision_print_nulls(value_buffer, buffer, Formaters);
      value_buffer += s21_pseudo_strcat(value_buffer, buffer);
    } else if (Formaters.precision < Formaters.width) {
      value_buffer += value_width(value_buffer, buffer, Formaters);
    }
  }
}

void value_str_creator(char *value_buffer, char *buffer,
                       struct form Formaters) {
  if ((int)s21_strlen(buffer) <= Formaters.precision) {
    if (Formaters.width > (int)s21_strlen(buffer)) {
      s21_size_t diff_width = Formaters.width - s21_strlen(buffer);
      if (Formaters.minus_count == 0) {
        value_buffer += width_print_spaces(value_buffer, Formaters, diff_width);
        value_buffer += s21_pseudo_strcat(value_buffer, buffer);
      } else {
        value_buffer += s21_pseudo_strcat(value_buffer, buffer);
        value_buffer += width_print_spaces(value_buffer, Formaters, diff_width);
      }
    } else
      value_buffer += s21_pseudo_strcat(value_buffer, buffer);
  } else if ((int)s21_strlen(buffer) > Formaters.precision) {
    if (Formaters.width > Formaters.precision && Formaters.precision > 0) {
      s21_size_t diff_width = Formaters.width - Formaters.precision;
      if (Formaters.minus_count == 0) {
        value_buffer += width_print_spaces(value_buffer, Formaters, diff_width);
        value_buffer +=
            writing_a_string(value_buffer, buffer, Formaters.precision);
      } else {
        value_buffer +=
            writing_a_string(value_buffer, buffer, Formaters.precision);
        value_buffer += width_print_spaces(value_buffer, Formaters, diff_width);
      }
    } else if (Formaters.width > Formaters.precision &&
               Formaters.precision == -1) {
      s21_size_t diff_width = Formaters.width - s21_strlen(buffer);
      if (Formaters.minus_count == 0) {
        value_buffer += width_print_spaces(value_buffer, Formaters, diff_width);
        value_buffer += s21_pseudo_strcat(value_buffer, buffer);
      } else {
        value_buffer += s21_pseudo_strcat(value_buffer, buffer);
        value_buffer += width_print_spaces(value_buffer, Formaters, diff_width);
      }
    } else if (Formaters.width > Formaters.precision &&
               Formaters.precision == 0) {
      value_buffer += width_print_spaces(value_buffer, Formaters,
                                         (s21_size_t)Formaters.width);
    } else if (Formaters.width <= Formaters.precision &&
               Formaters.precision > 0) {
      value_buffer +=
          writing_a_string(value_buffer, buffer, Formaters.precision);
    } else if (Formaters.width == -1 && Formaters.precision == -1) {
      value_buffer += s21_pseudo_strcat(value_buffer, buffer);
    }
  }
}

void value_char_creator(char *value_buffer, char *buffer,
                        struct form Formaters) {
  if (Formaters.width > 0) {
    if (Formaters.minus_count == 0) {
      value_buffer += width_print_spaces(value_buffer, Formaters,
                                         (s21_size_t)Formaters.width - 1);
      value_buffer += s21_pseudo_strcat(value_buffer, buffer);
    } else {
      value_buffer += s21_pseudo_strcat(value_buffer, buffer);
      value_buffer += width_print_spaces(value_buffer, Formaters,
                                         (s21_size_t)Formaters.width - 1);
    }
  } else if (Formaters.width == -1) {
    value_buffer += s21_pseudo_strcat(value_buffer, buffer);
  }
}

int value_flags_check(char *value_buffer, struct form Formaters) {
  int count = 0;
  if (Formaters.flags_check == 1) {
    if (Formaters.space_count == 1 && Formaters.negative_number == 0) {
      *value_buffer++ = ' ';
      count++;
    }
    if (Formaters.plus_count == 1 && Formaters.negative_number == 0) {
      *value_buffer++ = '+';
      count++;
    }
    if (Formaters.negative_number == 1) {
      *value_buffer++ = '-';
      count++;
    }
  } else {
    if (Formaters.negative_number == 1) {
      *value_buffer++ = '-';
      count++;
    }
  }
  return count;
}

s21_size_t precision_print_nulls(char *value_buffer, char *buffer,
                                 struct form Formaters) {
  s21_size_t diff_precision_strlen = Formaters.precision - s21_strlen(buffer);
  s21_size_t count = diff_precision_strlen;
  while (diff_precision_strlen > 0) {
    *value_buffer++ = '0';
    diff_precision_strlen--;
  }
  return count;
}

int value_width(char *value_buffer, char *buffer, struct form Formaters) {
  int count = 0;
  s21_size_t diff_width = 0;
  if (Formaters.precision < Formaters.width &&
      (int)s21_strlen(buffer) < Formaters.width &&
      (int)s21_strlen(buffer) < Formaters.precision) {
    diff_width = Formaters.width - Formaters.precision;
  } else
    diff_width = Formaters.width - s21_strlen(buffer);
  if (Formaters.minus_count == 0) {
    if (Formaters.plus_count == 1 || Formaters.negative_number == 1)
      diff_width--;
    if (Formaters.null_count == 0)
      value_buffer += width_print_spaces(value_buffer, Formaters, diff_width);
    if (Formaters.plus_count == 1 && Formaters.negative_number == 0) {
      *value_buffer++ = '+';
      count++;
    } else if (Formaters.negative_number == 1) {
      *value_buffer++ = '-';
      count++;
    }
    if (Formaters.null_count == 1 && Formaters.precision <= 0) {
      if (Formaters.space_count == 1 && Formaters.negative_number == 0)
        *value_buffer++ = ' ';
      value_buffer += width_print_spaces(value_buffer, Formaters, diff_width);
    }
    if (Formaters.precision > 0 &&
        (int)s21_strlen(buffer) < Formaters.precision &&
        Formaters.precision < Formaters.width)
      value_buffer += precision_print_nulls(value_buffer, buffer, Formaters);
    value_buffer += s21_pseudo_strcat(value_buffer, buffer);
    if (Formaters.f == 1 && Formaters.sharp == 1 && Formaters.precision == 0)
      *value_buffer++ = '.';
  } else if (Formaters.minus_count == 1) {
    value_buffer += value_flags_check(value_buffer, Formaters);
    if (Formaters.precision > 0 &&
        (int)s21_strlen(buffer) < Formaters.precision &&
        Formaters.precision < Formaters.width)
      value_buffer += precision_print_nulls(value_buffer, buffer, Formaters);
    value_buffer += s21_pseudo_strcat(value_buffer, buffer);
    if (Formaters.f == 1 && Formaters.sharp == 1 && Formaters.precision == 0)
      *value_buffer++ = '.';
    if (Formaters.plus_count == 1 || Formaters.negative_number == 1)
      diff_width--;
    if (Formaters.space_count == 1 && Formaters.negative_number == 0)
      diff_width--;
    value_buffer += width_print_spaces(value_buffer, Formaters, diff_width);
  }
  return count;
}

s21_size_t width_print_spaces(char *value_buffer, struct form Formaters,
                              s21_size_t diff_width) {
  s21_size_t count = diff_width;
  if (Formaters.sharp == 1) {
    diff_width--;
    count = diff_width;
  }
  if (Formaters.null_count == 1) {
    if (Formaters.space_count == 1 && Formaters.negative_number == 0) {
      diff_width--;
      count = diff_width;
    }
    while (diff_width > 0) {
      *value_buffer++ = '0';
      diff_width--;
    }
  } else {
    while (diff_width > 0) {
      *value_buffer++ = ' ';
      diff_width--;
    }
  }
  return count;
}

s21_size_t writing_a_string(char *dest, char *src, int count) {
  for (int i = 0; i < count; i++) {
    *dest++ = *src++;
  }
  return count;
}

long int lenght_change_d(long int val, int lenghtType) {
  if (lenghtType == 1) {
    val = (short int)val;
  } else if (lenghtType == 2) {
    val = (long int)val;
  } else {
    val = (int)val;
  }
  return val;
}

unsigned long int lenght_change_u(unsigned long int val, int lenghtType) {
  if (lenghtType == 1) {
    val = (unsigned short int)val;
  } else if (lenghtType == 2) {
    val = (unsigned long int)val;
  } else {
    val = (unsigned int)val;
  }
  return val;
}

int lenght_check(const char **sym) {
  int lenght = 0;
  if (*(*sym) == 'h') {
    lenght = 1;
    (*sym)++;
  } else if (*(*sym) == 'l') {
    lenght = 2;
    (*sym)++;
  }
  return lenght;
}

s21_size_t s21_pseudo_strcat(char *dest, char *src) {
  s21_size_t count = 0;
  for (count = 0; count < s21_strlen(src); count++) {
    *dest++ = src[count];
  }
  return count;
}