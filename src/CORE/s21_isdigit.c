#include "../s21_string.h"

int s21_isdigit(char ch) {
  int res = ((ch) >= '0' && (ch) <= '9');
  return res;
}