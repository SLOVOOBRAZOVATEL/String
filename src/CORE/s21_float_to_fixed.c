#include "../s21_string.h"

void s21_float_to_fixed(char *buffer, long double value, long precision) {
  s21_memset(buffer, 0, 256);

  char temp[256] = {0};
  long pos = 0;

  if (value < 0) {
    temp[pos++] = '-';
    value = -value;
  }

  long int_part = (long)value;
  long double frac_part = value - int_part;

  char int_buffer[20] = {0};
  long int_pos = 0;
  do {
    int_buffer[int_pos++] = (int_part % 10) + '0';
    int_part /= 10;
  } while (int_part > 0);

  for (long i = int_pos - 1; i >= 0; i--) {
    temp[pos++] = int_buffer[i];
  }

  if (precision > 0) {
    temp[pos++] = '.';
    for (long i = 0; i < precision; i++) {
      frac_part *= 10;
      long digit = (long)frac_part;
      temp[pos++] = digit + '0';
      frac_part -= digit;
    }

    if (frac_part * 10 >= 5) {
      int flag = 1;
      for (long i = pos - 1; i >= 0 && flag; i--) {
        if (temp[i] == '9') {
          temp[i] = '0';
        } else {
          temp[i]++;
          flag = 0;
        }
      }
    }
  }

  temp[pos] = '\0';
  s21_strncpy(buffer, temp, 255);
}
