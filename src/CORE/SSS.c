#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

#define ONE_PAGE 4096
#define S21_NULL ((void *)0)
typedef long unsigned s21_size_t;
#define s21_isNan(x) __builtin_isnan(x)

// #include "Headers/s21_sprintf.h"

#define BUFF_SIZE 4096

struct Flags {
  int plus;   // + для положительных
  int minus;  // -?
  int spase;  // ?
  int grid;   // ?
  int zero;   //
};

struct FormatData {
  struct Flags flags;  // флаги форматирования
  int counter;         // кол во обработанных символов
  int width;           // ширина поля вывода
  int precision;       // кол во знаков после запятой
  int has_precision;   // наличие точности
  char length;         // тип данных short/long
  char specifier;      // тип данных форматирования %d
};

int s21_sprintf(char *str, const char *format, ...);
int writeToStr(char *str, const char *format);
const char *formatParser(const char *format, struct FormatData *formatData,
                         int *flag, va_list va);
const char *getFlags(const char *format, struct FormatData *formatData);
const char *getWidth(const char *format, struct FormatData *formatData,
                     va_list va);
const char *getPrecision(const char *format, struct FormatData *formatData,
                         va_list va);
const char *getLength(const char *format, struct FormatData *formatData);
const char *getSpecifier(const char *format, struct FormatData *formatData,
                         int *flag);
int processSpecifier(char **str, struct FormatData *formatData, va_list va,
                     int res);
int processChar(char **str, va_list va, struct FormatData *formatData);
int processString(char *str, va_list va, struct FormatData *formatData);
int setSpaces(char *str, struct FormatData *formatData);
int processD(char *str, struct FormatData *formatData, va_list va);
int numberOfSymbolsInInt(long long int value);
int intToStr(char *valueStr, long long int value,
             struct FormatData *formatData);
int setSign(char *str, long double value, struct FormatData *formatData);
int addZeroes(char *str, struct FormatData *formatData);
int decreaseSignWidth(long double value, struct FormatData *formatData);
int decreaseZeroesWidth(struct FormatData *formatData);
int processUnsigned(char *str, struct FormatData *formatData, va_list va);
int processN(va_list va, int res);
int writeInt(char *str, struct FormatData *formatData, long long value);
int setZeroes(char *str, struct FormatData *formatData);
int processP(char *str, struct FormatData *formatData, va_list va);
int decToHexOct(char *valueStr, unsigned long long value,
                struct FormatData *formatData, int base);
int processFloat(char *str, struct FormatData *formatData, va_list va);
int floatToStr(char *valueStr, struct FormatData *formatData,
               long double value);
int writeFloat(char *str, struct FormatData *formatData, long double value);
void putPoint(char **valueStr, struct FormatData *formatData);
long double decimalPartFloat(char **valueStr, long double right_side,
                             long long *precision,
                             struct FormatData *formatData);
void floatConverter(char *valueStr, long double value,
                    struct FormatData *formatData);
int numberOfSymbolsInFloat(long double value);
int writeUnsigned(char *str, struct FormatData *formatData,
                  unsigned long long value);
int numberOfSymbolsInUnsigned(unsigned long long value);
int unsignedToStr(char *valueStr, unsigned long long value,
                  struct FormatData *formatData);
int processX(char *str, struct FormatData *formatData, unsigned long value);
void upperStrX(char *valueStr);
void handleSpacesPrefix(char **str, struct FormatData *formatData,
                        unsigned long long value);
int processO(char *str, struct FormatData *formatData,
             unsigned long long value);
void writeE_Value(char *str, struct FormatData *formatData, long double value);
void expToStr(char *valueStr, struct FormatData *formatData, int exp_counter,
              long double value);
void writeG_Value(char *str, struct FormatData *formatData, long double value);
void remove_zero(char *str, struct FormatData *formatData);
void helperSpecG(char *valueStr, struct FormatData *formatData);
int checkIfNanOrInf(char *valueStr, struct FormatData *formatData,
                    long double value);
void flagMinusHendler(char *str, char *valueStr, struct FormatData *formatData,
                      long double value);

// #include "Headers/s21_sscanf.h"

void *s21_memchr(const void *str, int c, s21_size_t n);  // DONE -- TEST
int s21_memcmp(const void *str1, const void *str2,
               s21_size_t n);  // DONE -- TEST 1 0 -1 or...
void *s21_memcpy(void *dest, const void *src, s21_size_t n);   // DONE
void *s21_memmove(void *dest, const void *src, s21_size_t n);  // DONE -- TEST
void *s21_memset(void *str, int c, s21_size_t n);              // DONE
char *s21_strcat(char *dest, const char *src);                 // DONE
char *s21_strncat(char *dest, const char *src, s21_size_t n);  // DONE
char *s21_strchr(const char *str, int c);                      // DONE
int s21_strcmp(const char *str1,
               const char *str2);  // DONE -- TEST 1 0 -1 or...
int s21_strncmp(const char *str1, const char *str2,
                s21_size_t n);                  // DONE -- TEST 1 0 -1 or...
char *s21_strcpy(char *dest, const char *src);  // DONE
char *s21_strncpy(char *dest, const char *src, s21_size_t n);  // DONE
s21_size_t s21_strcspn(const char *str1,
                       const char *str2);  // DONE test when NULL str
char *s21_strerror(int errnum);            // REPLACE sprintf to s21_sprintf
s21_size_t s21_strlen(const char *str);    // DONE
char *s21_strpbrk(const char *str1, const char *str2);       // DONE
char *s21_strrchr(const char *str, int c);                   // DONE
s21_size_t s21_strspn(const char *str1, const char *str2);   // DONE
char *s21_strstr(const char *haystack, const char *needle);  // DONE -- TEST
char *s21_strtok(char *str, const char *delim);              // DONE

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
s21_size_t s21_strspn_reverse(const char *str1, const char *str2);
int s21_atoi(char *str);
long s21_atol(char *str);

int s21_sprintf(char *str, const char *format, ...) {
  va_list va;  // работа с переменными аргументами
  va_start(va, format);  // инициализация для получения аргументов
  int flag = 1;  // флаг для формата
  int res =
      0;  // счетчик для хранения количества записанных символов, возвращаемый
  struct FormatData formatData = {0};
  str[0] = '\0';  // обнуление строки, для записи

  while (*format) {
    if (flag) {
      s21_memset(&formatData, 0, sizeof(formatData));  // заполнение нулями
      if (*format == '%') {
        format++;
        format = formatParser(format, &formatData, &flag, va);
        processSpecifier(&str, &formatData, va, res);
        res += formatData.counter;
      } else {
        writeToStr(str, format);
        res++;
        format++;
      }
    } else {
      printf("error");
      *str = '\0';
      break;
    }
  }
