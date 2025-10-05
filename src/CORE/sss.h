#ifndef SRC_S21_SPRINTF_H_
#define SRC_S21_SPRINTF_H_

//#include <math.h>
#include <stdarg.h>
//#include <stdint.h>
//#include <stdlib.h>
//#include <locale.h>
//#include <wchar.h>

#include "../s21_string.h"
#define BUF 10000
// typedef enum Format {
//     NOT_VALID,
//     IS_SPEC,
//     IS_FLAG,
//     IS_WIDTH,
//     IS_PRECISION,
//     IS_LENGTH,
//     IS_PERCENT
// };

// typedef enum Lengths { FLAGS_LEN = 3, LENGTHS_LEN = 2, SPECS_LEN = 7 };

// #define FLAGS_LIST "+- "
// #define SPECS_LIST "cdifsu%"
// #define LENGTH_LIST "hl"

// typedef struct flag {
//     int plus;
//     int minus;
//     int space;
// };

// typedef struct length {
//     int h_enabled;
//     int l_enabled;
// };

// typedef struct spec {
//     int c_enabled;
//     int d_enabled;
//     int i_enabled;
//     int f_enabled;
//     int s_enabled;
//     int u_enabled;
// };

// typedef struct formating {
//     struct flag flag;
//     int width;
//     int precision;
//     struct length length;
//     struct spec spec;
// };


typedef struct spec {
  int c;
  int d;
  int f;
  int s;
  int u;
  int h; 
  int l; 
  int alig;  // значение цифр после минуса, выравнивание
  int plus;
  int minus;
  int space;
  int width;  // значение цифр после пробела, ширина
  int point; 
  long int accuracy;  // значение цифр после точки, точность
  int BD;             // Boulevard Depo - otricala
  // BD: f: if (f < 0)
  int BD_d;       // d: if (d < 0 && spec->plus)
  int BD_d2;      // d: if (d < 0 && spec->point)
  int BD_f;       // f: if (f < 0 && spec->plus)
  int BD_f_plus;  // f: if (spec->plus && f >= 0)
  int f_int;      // если double целое число
  int sm;         // f: if (f < 0 && spec->minus)
  int zero_acc;  // счетчик добавленных нулей при spec->point
  int zero_acc_u;  // счетчик добавленных нулей при spec->point для u
  short int s_i;            // d: short int
  long int l_i;             // d: long int
  wchar_t wc;               // c: width char
  unsigned short int us_i;  // u: Unsigned Short Int
  unsigned long int ul_i;   // u: Unsigned Long Int
  int flag_for_plus;        // d: if (spec->point && spec->plus)
  int flag_for_plus_f;      // f: if (spec->plus)
  int flag_for_plus_f2;     // f: флаг добавления '+'
} Specifiers;

typedef struct err {
  int exit;
  int plus_space;
  int plus_c;
  int plus_s;
  int plus_u;
  int space_c;
  int space_s;
  int space_u;
} Errors;

#endif  