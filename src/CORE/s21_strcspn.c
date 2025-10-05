
#include "../s21_string.h"
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const unsigned char *ptr1 = (const unsigned char *)str1;
  const unsigned char *ptr2 = (const unsigned char *)str2;
  int result = 0;
  int last_res = 0;
  int f = 1;
  for (int i = 0; ptr2[i] != '\0' && f != 2; i++) {
    if ((f == 0) && (result > last_res)) {
      last_res = result;
      result = 0;
      f = 1;
    }
    if (f == 1) {
      result = 0;
    }
    for (int j = 0; ptr1[j] != '\0' && f != 2; j++) {
      if ((ptr1[j] == ptr2[i]) && (result == 0) && (last_res == 0) &&
          (f == 1)) {
        f = 2;
      } else if ((ptr1[j] == ptr2[i]) && (f == 1)) {
        f = 0;
      }
      if (f == 1) {
        result++;
      }
    }
  }
  if (*ptr2 == '\0') {
    result = s21_strlen(str1);
  }
  return result;
}