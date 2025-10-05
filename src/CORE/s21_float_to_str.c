#include "../s21_string.h"

char *s21_float_to_str(long double value, long precision, int use_exponential,
                       int is_upper) {
  static char buffer[256];
  s21_memset(buffer, 0, sizeof(buffer));

  char temp[256] = {0};
  long pos = 0;

  if (use_exponential) {
    long exponent = 0;
    if (value != 0.0) {
      while (fabs((double)value) >= 10.0) {
        value /= 10.0;
        exponent++;
      }
      while (fabs((double)value) < 1.0) {
        value *= 10.0;
        exponent--;
      }
    }

    long int_part = (long)value;
    long double frac_part = value - int_part;

    temp[pos++] = int_part + '0';
    if (precision > 0) {
      temp[pos++] = '.';
      for (long i = 0; i < precision; i++) {
        frac_part *= 10;
        long digit = (long)frac_part;
        temp[pos++] = digit + '0';
        frac_part -= digit;
      }
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

    temp[pos++] = is_upper ? 'E' : 'e';
    if (exponent < 0) {
      temp[pos++] = '-';
      exponent = -exponent;
    } else {
      temp[pos++] = '+';
    }

    temp[pos++] = (exponent / 10) + '0';
    temp[pos++] = (exponent % 10) + '0';
  } else {
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
    }

    if (frac_part * 10 >= 5) {
      int flag = 1;
      for (long i = pos - 1; i >= 0 && flag; i--) {
        if (temp[i] == '.') {
        } else if (temp[i] == '9') {
          temp[i] = '0';
        } else {
          temp[i]++;
          flag = 0;
        }
      }
    }
  }

  temp[pos] = '\0';
  s21_strncpy(buffer, temp, sizeof(buffer) - 1);
  return buffer;
}
