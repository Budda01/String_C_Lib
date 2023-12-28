#include "s21_string.h"

int s21_sscanf(char *str, const char *format, ...) {
  int count = 0;
  struct form Formaters = {0};
  va_list arguments;
  va_start(arguments, format);
  const char *st = str;
  const char *sym = format;
  for (; *sym; sym++) {
    if (*sym != '%') {
      continue;
    } else {
      sym++;
      s21_memset(&Formaters, 0, sizeof(Formaters));
    }
    get_specifier_scanf(&sym, &Formaters);
    count = work_space_sscanf(&st, &arguments, count);
  }

  va_end(arguments);
  return count;
}

void get_specifier_scanf(const char **sym, struct form *Formaters) {
  switch (**sym) {
    case 'c':
      Formaters->s = 1;
      break;
    default:
      break;
  }
}

int work_space_sscanf(char const **st, va_list *arguments, int count) {
  char *val = va_arg(*arguments, char *);
  *val++ = **st++;
  *val = '\0';
  count++;
  return count;
}
