#include <stdio.h>

#include "../s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  if ((dest != s21_NULL && src != s21_NULL) &&
      (dest[s21_strlen(dest)] == '\0') && (src[s21_strlen(src)] == '\0')) {
    char *ptr = dest + s21_strlen(dest);
    while (*src != '\0') {
      *ptr++ = *src++;
    }
    *ptr = '\0';
  } else {
    dest = s21_NULL;
  }
  return dest;
}