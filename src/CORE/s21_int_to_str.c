#include "../s21_string.h"

char *s21_int_to_str(long value, long base, int is_upper, int is_unsigned) {
  static char buffer[65];
  const char *digits = is_upper ? "0123456789ABCDEF" : "0123456789abcdef";

  if (base < 2 || base > 36) {
    return NULL;
  }

  char *ptr = buffer + sizeof(buffer) - 1;
  *ptr = '\0';

  if (value == 0) {
    *(--ptr) = '0';
  } else {
    unsigned long uvalue =
        is_unsigned ? (unsigned long)value : (value < 0 ? -value : value);

    while (uvalue > 0) {
      *(--ptr) = digits[uvalue % base];
      uvalue /= base;
    }

    if (!is_unsigned && value < 0) {
      *(--ptr) = '-';
    }
  }

  return ptr;
}