#ifndef S21_STRING_H
#define S21_STRING_H

#define s21_NULL \
  ((void *)0)  // Это значение называется "нулевым указательным константом"
#define FLAGS_LIST "+- #0"
#define SPECS_LIST "cdifsugGeExXop%"
#define LENGTH_LIST "hlL"

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

typedef enum {
  NOT_VALID,
  IS_SPEC,
  IS_FLAG,
  IS_WIDTH,
  IS_PRECISION,
  IS_LENGTH,
  IS_PERCENT
} Format;

typedef struct {
  int plus;
  int minus;
  int space;
  int sharp;
  int zero;
} flag;

typedef struct {
  int h_enabled;
  int l_enabled;
  int L_enabled;
} length;

typedef struct {
  int c_enabled;
  int d_enabled;
  int f_enabled;
  int s_enabled;
  int u_enabled;
  int g_enabled;
  int G_enabled;
  int e_enabled;
  int E_enabled;
  int x_enabled;
  int X_enabled;
  int o_enabled;
  int p_enabled;
  int percent_enabled;
} spec;

typedef struct {
  flag flag;
  int width;
  int precision;
  length length;
  spec spec;
} formating;

typedef long unsigned s21_size_t;

int s21_isdigit(char ch);

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);

char *s21_strcat(char *dest, const char *src);

char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);

int s21_sprintf(char *str, const char *format, ...);
void s21_parse_format(const char **ptr, formating *fmt, va_list args);
char *s21_int_to_str(long value, long base, int is_upper, int is_unsigned);
char *s21_float_to_str(long double value, long precision, int use_exponential,
                       int is_upper);
char *s21_float_to_g_str(long double value, long precision);
void s21_float_to_fixed(char *buffer, long double value, long precision);
void s21_add_decimal_point(char *formatted);

#endif
