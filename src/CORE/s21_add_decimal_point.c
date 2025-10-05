#include "../s21_string.h"

void s21_add_decimal_point(char *formatted) {
  if (s21_strchr(formatted, '.') == s21_NULL) {
    s21_size_t len = s21_strlen(formatted);
    if (len < 255) {
      formatted[len] = '.';
      formatted[len + 1] = '\0';
    }
  }
}
