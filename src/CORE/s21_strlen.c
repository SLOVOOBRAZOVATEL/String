#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  const unsigned char *ptr = (const unsigned char *)str;
  s21_size_t len = 0;
  if (ptr) {
    while (ptr[len]) {
      len++;
    }
  }
  return len;
}