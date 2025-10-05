#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  const unsigned char *ptr = (const unsigned char *)str;
  void *res = s21_NULL;
  while (*ptr) {
    if (*ptr == c) {
      res = (void *)ptr;
    }
    ptr++;
  }
  if (c == '\0') {
    res = (void *)ptr;
  }
  return (char *)res;
}