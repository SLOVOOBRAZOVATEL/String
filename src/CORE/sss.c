#include "sss.h"
#include <stdio.h>


int s21_sprintf(char *str, const char *format,...);
void s21_reading_error(const char *buffer, Specifiers *spec, Errors *err);
const char *s21_parser_flags_error(Specifiers *spec, const char *buffer, Errors *err);
const char *s21_parser_flags(Specifiers *spec,const char *buffer);
const char *s21_alignment(const char *buffer, Specifiers *spec);
const char *s21_get_width(const char *buffer, Specifiers *spec);
const char *s21_get_point(const char *format, Specifiers *spec);
const char *s21_parser_length(Specifiers *spec, const char *format);
const char *s21_parser_spec(Specifiers *spec,const char *buffer);
void s21_print_errors(Errors *err);
void s21_read_str(char *str, const char *format, va_list args,
                  Specifiers *spec);




int main() {
    char arr[100];
    int age = 25;
    double height = 1.75;
    const char *name = "Alice";

    // Форматируем строку с использованием sprintf
    int n = s21_sprintf(arr, "Name: %s, Age: %d, Height: %.2f", name, age, height);

    // Выводим отформатированную строку
    printf("Formatted string: %s\n", arr);
    printf("Number of characters written: %d\n", n);

    return 0;
}

int s21_sprintf(char *str, const char *format,...){
    char* destination = str;
    const char* buffer = (const char*) format;

Specifiers spec = {0};
  Errors err = {0};

    va_list args;
    int result = 0;
    
    if (str == s21_NULL){
        result = -1;
    }else{
        va_start(args, buffer);

            //%[флаги][ширина][.точность][длина]спецификатор
        s21_reading_error(buffer, &spec, &err);
        if (err.exit){
            s21_print_errors(&err);
            return 1;
        }
        
        s21_read_str(str, format, args, &spec);
        result = s21_strlen(str);
        va_end(args);
    }
return result;
}

void s21_reading_error(const char *buffer, Specifiers *spec, Errors *err) {
  while (*buffer != '\0') {
    if (*buffer == '%') {
      s21_parser_flags_error(spec, buffer, err);
    }
    buffer++;
  }
}

const char *s21_parser_flags_error(Specifiers *spec, const char *buffer,
                                   Errors *err) {  // + - space
  buffer = s21_parser_flags(spec, buffer);
  if (spec->minus) {
    buffer = s21_alignment(buffer, spec);
  } else {
    buffer = s21_get_width(buffer, spec);
  }
  if (*buffer == '.') {
    buffer++;
    spec->point = 1;
    buffer = s21_get_point(buffer, spec);
  }
  buffer = s21_parser_length(spec, buffer);
  buffer = s21_parser_spec(spec, buffer);
  if (spec->space && spec->plus) err->plus_space = 1, err->exit = 1;
  if (spec->plus && spec->c) err->plus_c = 1, err->exit = 1;
  if (spec->plus && spec->s) err->plus_s = 1, err->exit = 1;
  if (spec->plus && spec->u) err->plus_u = 1, err->exit = 1;
  if (spec->space && spec->c) err->space_c = 1, err->exit = 1;
  if (spec->space && spec->s) err->space_s = 1, err->exit = 1;
  if (spec->space && spec->u) err->space_u = 1, err->exit = 1;

  s21_memset(spec, 0, sizeof(Specifiers));
  return buffer;
}

const char *s21_parser_flags(Specifiers *spec,const char *buffer) {  // + - space
  buffer++;
  char speci[100] = "1234567890\0";
  // считывание от '%' до любой цифры
  for (s21_size_t i = 0; i < s21_strcspn(buffer, speci) + 1; i++) {
    switch (*buffer) {
      case '+':
        spec->plus = 1;
        buffer++;
        break;
      case '-':
        spec->minus = 1;
        buffer++;
        break;
      case ' ':
        spec->space = 1;
        buffer++;
        break;
    }
  }
  return buffer;
}

const char *s21_alignment(const char *buffer, Specifiers *spec) {
  char speci[100] = ".cdsufhl\0";
  // взятие числа при минусе
  int j = (int)s21_strcspn(buffer, speci);
  for (int i = 0; i < j; i++) {
    if (j == 1) {
      spec->alig = *buffer - 48;
    } else {
      spec->alig = spec->alig * 10 + (*buffer - 48);
    }
    buffer++;
  }
  return buffer;
}

const char *s21_get_width(const char *buffer, Specifiers *spec) {
  char speci[100] = ".cdsufhl\0";
  // взятие числа при ширине
  int j = (int)s21_strcspn(buffer, speci);
  for (int i = 0; i < j; i++) {
    if (j == 1) {                    // для одной цифры
      spec->width = *buffer - 48;  // 1: 49 - 48 = 1; по ascii таблице
    } else {                         // для более одной
      spec->width = spec->width * 10 + (*buffer - 48);
      // 12: 1 * 10 = 10; 10 + 2 = 12
    }
    buffer++;
  }
  return buffer;
}

const char *s21_get_point(const char *format, Specifiers *spec) {
  char speci[100] = "cdsufhl\0";
  // взятие точности
  int j = (int)s21_strcspn(format, speci);
  for (int i = 0; i < j; i++) {
    if (j == 1) {
      spec->accuracy = *format - 48;
    } else {
      spec->accuracy = spec->accuracy * 10 + (*format - 48);
    }
    format++;
  }
  return format;
}

const char *s21_parser_length(Specifiers *spec, const char *format) {
  char speci[100] = "cdsuf\0";
  // считывание флагов h и l до любого спецификатора
  for (s21_size_t i = 0; i < s21_strcspn(format, speci); i++) {
    switch (*format) {
      case 'h':
        spec->h = 1;
        format++;
        break;
      case 'l':
        spec->l = 1;
        format++;
        break;
    }
  }
  return format;
}

const char *s21_parser_spec(Specifiers *spec,const char *buffer) {  // c d s u f
  for (int i = 0; i < 1; i++) {
    switch (*buffer) {
      case 'c':
        spec->c = 1;
        break;
      case 'd':
        spec->d = 1;
        break;
      case 's':
        spec->s = 1;
        break;
      case 'u':
        spec->u = 1;
        break;
      case 'f':
        spec->f = 1;
        break;
    }
  }
  return buffer;
}

void s21_print_errors(Errors *err) {
  if (err->plus_space) {
    char plus_space[BUF] =
        "error: ' ' flag ignored with '+' flag in gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->plus_c) {
    char plus_space[BUF] = "error: '+' flag used with '%c' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->plus_s) {
    char plus_space[BUF] = "error: '+' flag used with '%s' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->plus_u) {
    char plus_space[BUF] = "error: '+' flag used with '%u' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->space_c) {
    char plus_space[BUF] = "error: ' ' flag used with '%c' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->space_s) {
    char plus_space[BUF] = "error: ' ' flag used with '%s' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  if (err->space_u) {
    char plus_space[BUF] = "error: ' ' flag used with '%u' gnu_printf format";
    fprintf(stderr, "%s\n", plus_space);
  }
  printf("FIX ANY ERROR(S) TO CONTINUE\r");
  s21_memset(err, 0, sizeof(Errors));
}

void s21_read_str(char *str, const char *format, va_list args,
                  Specifiers *spec){
                    int flag = 0;  // флаг добавления ' ' при spec->space
  while (*format != '\0') {
    if (*format != '%') {
      s21_putchar_to_str(*format, str);
    } else if (*format == '%') {
      // format = [function] - это перемещение указателя, если прошли условия
      // функции
      format = s21_parser_flags(spec, format);
      if (spec->minus) {
        format = s21_alignment(format, spec);
      } else {
        format = s21_get_width(format, spec);
      }
      if (*format == '.') {
        format++;
        spec->point = 1;
        format = s21_get_point(format, spec);
      }
      format = s21_parser_length(spec, format);
      format = s21_parser_spec(spec, format);
      if (spec->d) s21_spec_d(args, spec, str, flag);
      if (spec->c) s21_spec_c(args, spec, str);
      if (spec->s) s21_spec_s(args, spec, str, flag);
      if (spec->u) s21_spec_u(args, spec, str, flag);
      if (spec->f) s21_spec_f(args, spec, str, flag);
    }
    format++;
  }
}

int s21_putchar_to_str(const char c, char *str) {
  while (*str) {
    str++;
  }          // доходим до конца строки
  *str = c;  // приравниваем указатель к символу
  str++;
  *str = '\0';
  return 1;
}
                  
void s21_spec_d(va_list args, Specifiers *spec, char *str, int flag) {
  char temp[BUF] = {'\0'};
  int above_zero = 0;  // флаг, если число больше 0
  s21_init_d(args, spec, &above_zero, temp);
  if (spec->point) {
    if (spec->plus) spec->flag_for_plus = 1;
    for (int i = 0; i < spec->accuracy - (int)s21_strlen(temp); i++) {
      spec->zero_acc++;  // счетчик добавленных нулей при точности
    }
  }
  if (spec->space && above_zero) s21_add_space(spec, str, &flag);
  s21_space_width(temp, str, spec, &flag);
  if (spec->point) {
    if (spec->plus &&
        !spec->BD_d) {  // добавление '+', если положительное число
      s21_putchar_to_str('+', str);
      spec->plus = 0;
    }
    if (spec->BD_d2) {
      s21_putchar_to_str('-', str);
    }
    for (int i = 0; i < spec->accuracy - (int)s21_strlen(temp);
         i++) {  // добавление '0', если точность
      s21_putchar_to_str('0', str);
    }
    spec->accuracy = 0, spec->point = 0;
  }
  s21_strncat(str, temp, BUF);
  s21_space_minus(temp, str, spec, &flag);
  spec->zero_acc = 0, spec->flag_for_plus = 0, spec->plus = 0;
  spec->d = 0, spec->BD_d = 0, spec->space = 0, above_zero = 0, spec->BD_d2 = 0;
}
void s21_spec_c(va_list args, Specifiers *spec, char *str) {
  if (spec->shirina) {
    for (int i = 0; i < spec->shirina - 1; i++) {  // space_width
      s21_putchar_to_str(' ', str);
    }
    spec->shirina = 0;
  }
  if (spec->l) {
    spec->wc = va_arg(args, wchar_t);
    s21_putchar_to_str(spec->wc, str);
    spec->l = 0;
  } else {
    char c = va_arg(args, int);
    s21_putchar_to_str(c, str);
  }
  if (spec->minus) {                            // space_minus
    for (int i = 0; i < spec->alig - 1; i++) {  // -1: strlen(c)
      s21_putchar_to_str(' ', str);
    }
    spec->minus = 0, spec->alig = 0;
  }
  spec->c = 0;
}
void s21_spec_s(va_list args, Specifiers *spec, char *str, int flag) {
  char *s = va_arg(args, char *);
  if (spec->point) {
    for (int i = spec->accuracy; i < (int)s21_strlen(s) && s[i] != '\0'; i++) {
      s[i] = '\0';
    }
    spec->point = 0, spec->accuracy = 0;
  }
  s21_space_width(s, str, spec, &flag);
  s21_strncat(str, s, BUF);
  s21_space_minus(s, str, spec, &flag);
  spec->s = 0;
}
void s21_spec_u(va_list args, Specifiers *spec, char *str, int flag) {
  char temp[BUF] = {'\0'};
  if (spec->h) {
    spec->us_i = va_arg(args, int);
    s21_unsigned_int_to_string(spec->us_i, temp);
    spec->h = 0;
  } else if (spec->l) {
    spec->ul_i = va_arg(args, long);
    s21_unsigned_int_to_string(spec->ul_i, temp);
    spec->l = 0;
  } else {
    unsigned int d = va_arg(args, int);
    s21_unsigned_int_to_string(d, temp);
  }
  if (spec->point) {
    for (int i = 0; i < spec->accuracy - (int)s21_strlen(temp); i++) {
      spec->zero_acc_u++;  // счетчик добавленных нулей при точности
    }
  }
  s21_space_width(temp, str, spec, &flag);
  if (spec->point) {  // можно сделать функцию
    for (int i = 0; i < spec->accuracy - (int)s21_strlen(temp); i++) {
      s21_putchar_to_str('0', str);
    }
    spec->accuracy = 0, spec->point = 0;
  }
  s21_strncat(str, temp, BUF);
  s21_space_minus(temp, str, spec, &flag);
  spec->u = 0, spec->zero_acc_u = 0;
}
void s21_spec_f(va_list args, Specifiers *spec, char *str, int flag) {
  int sp = 0;
  double f = va_arg(args, double);
  if ((f < 0 && spec->plus)) spec->BD_d = 1, spec->BD_f = 1;
  if (f < 0 && spec->space) sp = 1;
  if (f < 0 && spec->minus) spec->sm = 1;
  if (spec->point) {
    for (int i = 0; i < spec->accuracy; i++) f = f * 10.0;
    f = round(f);
    for (int i = 0; i < spec->accuracy; i++) f = f / 10.0;
  }
  if (spec->plus && f >= 0) spec->BD_f_plus = 1;

  char *temp = s21_float_to_string(f, spec);
  if (spec->point) spec->point = 0, spec->accuracy = 0;
  if (f >= 0 && !spec->BD_f_plus && !spec->BD_f && !sp)
    s21_add_space(spec, str, &flag);

  s21_space_width(temp, str, spec, &flag);
  s21_strncat(str, temp, BUF);
  s21_space_minus(temp, str, spec, &flag);
  spec->f = 0, spec->BD_d = 0, spec->plus = 0, spec->BD_f = 0,
  spec->BD_f_plus = 0, spec->flag_for_plus_f = 0, spec->flag_for_plus_f2 = 0,
  spec->shirina = 0, sp = 0, spec->sm = 0;
}