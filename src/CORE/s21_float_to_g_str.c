#include "../s21_string.h"

char *s21_float_to_g_str(long double value, long precision) {
  static char buffer[256];
  s21_memset(buffer, 0, sizeof(buffer));

  long double abs_value = value < 0 ? -value : value;

  if (abs_value < 1e-4 || abs_value >= pow(10, precision)) {
    const char *temp = s21_float_to_str(value, precision - 1, 1, 0);
    s21_strncpy(buffer, temp, s21_strlen(temp));
  } else {
    char temp[256];
    s21_float_to_fixed(temp, value, precision);
    s21_strncpy(buffer, temp, s21_strlen(temp));

    const char *dot_ptr = s21_strchr(buffer, '.');
    if (dot_ptr) {
      char *end = buffer + s21_strlen(buffer) - 1;
      while (end > dot_ptr && *end == '0') {
        *end-- = '\0';
      }
      if (*end == '.') {
        *end = '\0';
      }
    }
  }

  return buffer;
}
