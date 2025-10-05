#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const char *res = s21_NULL;
  const char *source = (const char *)str;
  if (str != s21_NULL) {
    do {
      if (*source == (char)c) {
        res = source;
      }
    } while (*source++);
  }
  return (char *)res;
}