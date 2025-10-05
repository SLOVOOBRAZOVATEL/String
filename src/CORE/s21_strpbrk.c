#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  void *res = s21_NULL;
  const char *str_1 = (const char *)str1;
  const char *str_2 = (const char *)str2;
  int f = 0;
  if ((str_1 == s21_NULL) || (str_2 == s21_NULL)) {
    f = 1;
  }
  while (f != 1 && *str_1) {
    if (!s21_strchr(str_2, *str_1)) {
      str_1++;
    } else {
      f = 1;
      res = (char *)str_1;
    }
  }
  return (char *)res;
}