#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *destination = dest;
  const unsigned char *source = (const unsigned char *)src;
  while (n--) {
    if (*source) {
      *destination++ = *source++;
    } else {
      *destination++ = '\0';
    }
  }
  return dest;
}