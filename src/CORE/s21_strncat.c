#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *destination = dest;
  const unsigned char *source = (const unsigned char *)src;
  while (*destination) {
    destination++;
  }
  while (n--) {
    *destination++ = *source++;
  }
  *destination = '\0';
  return dest;
}