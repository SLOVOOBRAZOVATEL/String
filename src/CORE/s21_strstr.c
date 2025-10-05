#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  void *res = s21_NULL;

  int f = 0;
  if (*needle == '\0') {
    res = (char *)haystack;
  }
  while (*haystack && f == 0) {
    const char *h = (const char *)haystack;
    const char *n = (const char *)needle;
    while (*n && *h == *n) {
      h++;
      n++;
    }
    if (*n == '\0') {
      res = (char *)haystack;
      f = 1;
    }
    haystack++;
  }
  return res;
}