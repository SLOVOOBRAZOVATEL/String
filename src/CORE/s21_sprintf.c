#include "../s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  const char *ptr = format;
  char *out = str;
  formating fmt;

  while (*ptr) {
    if (*ptr != '%') {
      *out++ = *ptr++;
    } else {
      ptr++;
      s21_parse_format(&ptr, &fmt, args);

      char buffer[256];
      s21_memset(buffer, 0, sizeof(buffer));

      if (fmt.spec.c_enabled) {
        int value = va_arg(args, int);
        buffer[0] = (char)value;
        buffer[1] = '\0';
      } else if (fmt.spec.d_enabled) {
        long value = fmt.length.l_enabled   ? va_arg(args, long)
                     : fmt.length.h_enabled ? (short)va_arg(args, int)
                                            : va_arg(args, int);
        const char *formatted = s21_int_to_str(value, 10, 0, 0);
        s21_strncpy(buffer, formatted, s21_strlen(formatted));
      } else if (fmt.spec.f_enabled || fmt.spec.g_enabled ||
                 fmt.spec.G_enabled) {
        long double value = fmt.length.L_enabled ? va_arg(args, long double)
                                                 : va_arg(args, double);
        if (fmt.precision < 0) fmt.precision = 6;

        int g_mode = fmt.spec.g_enabled || fmt.spec.G_enabled;
        const char *formatted =
            g_mode ? s21_float_to_g_str(value, fmt.precision)
                   : s21_float_to_str(value, fmt.precision, 0, fmt.flag.sharp);
        s21_strncpy(buffer, formatted, s21_strlen(formatted));
      } else if (fmt.spec.s_enabled) {
        const char *value = va_arg(args, char *);
        s21_strncpy(buffer, value, sizeof(buffer) - 1);
      } else if (fmt.spec.u_enabled) {
        unsigned long value = fmt.length.l_enabled ? va_arg(args, unsigned long)
                              : fmt.length.h_enabled
                                  ? (unsigned short)va_arg(args, unsigned int)
                                  : va_arg(args, unsigned int);
        const char *formatted = s21_int_to_str(value, 10, 0, 1);
        s21_strncpy(buffer, formatted, s21_strlen(formatted));
      } else if (fmt.spec.e_enabled || fmt.spec.E_enabled) {
        double value = fmt.length.L_enabled ? va_arg(args, long double)
                                            : va_arg(args, double);
        if (fmt.precision < 0) fmt.precision = 6;
        char *formatted =
            s21_float_to_str(value, fmt.precision, 1, fmt.spec.E_enabled);
        if (fmt.flag.sharp) {
          s21_add_decimal_point(formatted);
        }
        s21_strncpy(buffer, formatted, s21_strlen(formatted));
      } else if (fmt.spec.x_enabled || fmt.spec.X_enabled) {
        unsigned long value = fmt.length.l_enabled ? va_arg(args, unsigned long)
                              : fmt.length.h_enabled
                                  ? (unsigned short)va_arg(args, unsigned int)
                                  : va_arg(args, unsigned int);
        char *formatted = s21_int_to_str(value, 16, fmt.spec.X_enabled, 1);
        if (value == 0) {
          s21_strncpy(buffer, "0",
                      1);  // Если значение 0, просто записываем "0"
        } else {
          if (fmt.flag.sharp) {
            s21_strncpy(buffer, fmt.spec.X_enabled ? "0X" : "0x", 2);
          }
          s21_strcat(buffer, formatted);
        }
      } else if (fmt.spec.o_enabled) {
        unsigned long value = fmt.length.l_enabled ? va_arg(args, unsigned long)
                              : fmt.length.h_enabled
                                  ? (unsigned short)va_arg(args, unsigned int)
                                  : va_arg(args, unsigned int);
        char *formatted = s21_int_to_str(value, 8, 0, 1);
        if (fmt.flag.sharp) s21_strncpy(buffer, "0", 1);
        s21_strcat(buffer, formatted);
      } else if (fmt.spec.p_enabled) {
        void *value = va_arg(args, void *);
        char *formatted = s21_int_to_str((unsigned long)value, 16, 0, 1);
        s21_strncpy(buffer, "0x", 2);
        s21_strcat(buffer, formatted);
      } else if (fmt.spec.percent_enabled) {
        buffer[0] = '%';
        buffer[1] = '\0';
      }

      int len = s21_strlen(buffer);
      if (!fmt.flag.minus && len < fmt.width) {
        int pad = fmt.width - len;
        while (pad--) {
          *out++ = fmt.flag.zero ? '0' : ' ';
        }
      }

      if (s21_strchr(buffer, '-') == s21_NULL && !fmt.flag.plus &&
          fmt.flag.space)
        *out++ = ' ';
      if (fmt.flag.plus) *out++ = '+';
      s21_strncpy(out, buffer, s21_strlen(buffer));
      out += len;

      if (fmt.flag.minus && len < fmt.width) {
        int pad = fmt.width - len;
        while (pad--) {
          *out++ = ' ';
        }
      }
    }
  }

  *out = '\0';
  va_end(args);
  return (int)(out - str);
}

void s21_parse_format(const char **ptr, formating *fmt, va_list args) {
  s21_memset(fmt, 0, sizeof(formating));
  fmt->precision = -1;

  while (s21_strchr(FLAGS_LIST, **ptr)) {
    switch (*(*ptr)++) {
      case '+':
        fmt->flag.plus = 1;
        break;
      case '-':
        fmt->flag.minus = 1;
        break;
      case ' ':
        fmt->flag.space = 1;
        break;
      case '#':
        fmt->flag.sharp = 1;
        break;
      case '0':
        fmt->flag.zero = 1;
        break;
    }
  }

  if (**ptr == '*') {
    fmt->width = va_arg(args, int);
    (*ptr)++;
  } else {
    while (s21_isdigit(**ptr)) {
      fmt->width = fmt->width * 10 + (*(*ptr)++ - '0');
    }
  }

  if (**ptr == '.') {
    (*ptr)++;
    fmt->precision = 0;
    if (**ptr == '*') {
      fmt->precision = va_arg(args, int);
      (*ptr)++;
    } else {
      while (s21_isdigit(**ptr)) {
        fmt->precision = fmt->precision * 10 + (*(*ptr)++ - '0');
      }
    }
  }

  if (s21_strchr(LENGTH_LIST, **ptr)) {
    switch (*(*ptr)++) {
      case 'h':
        fmt->length.h_enabled = 1;
        break;
      case 'l':
        fmt->length.l_enabled = 1;
        break;
      case 'L':
        fmt->length.L_enabled = 1;
        break;
    }
  }

  if (s21_strchr(SPECS_LIST, **ptr)) {
    switch (*(*ptr)++) {
      case 'c':
        fmt->spec.c_enabled = 1;
        break;
      case 'd':
        fmt->spec.d_enabled = 1;
        break;
      case 'f':
        fmt->spec.f_enabled = 1;
        break;
      case 's':
        fmt->spec.s_enabled = 1;
        break;
      case 'u':
        fmt->spec.u_enabled = 1;
        break;
      case 'g':
        fmt->spec.g_enabled = 1;
        break;
      case 'G':
        fmt->spec.G_enabled = 1;
        break;
      case 'e':
        fmt->spec.e_enabled = 1;
        break;
      case 'E':
        fmt->spec.E_enabled = 1;
        break;
      case 'x':
        fmt->spec.x_enabled = 1;
        break;
      case 'X':
        fmt->spec.X_enabled = 1;
        break;
      case 'o':
        fmt->spec.o_enabled = 1;
        break;
      case 'p':
        fmt->spec.p_enabled = 1;
        break;
      case '%':
        fmt->spec.percent_enabled = 1;
        break;
    }
  }
}