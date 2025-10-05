#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t size_src = s21_strlen(src);
  s21_size_t size_str = s21_strlen(str);
  char *inserted = s21_NULL;

  if ((size_str != 0 || size_src != 0) && start_index <= size_src) {
    inserted = calloc(size_src + size_str + 2, 1);
    if (inserted != s21_NULL) {
      for (s21_size_t i = 0; i < start_index; i++) {
        inserted[i] = src[i];
      }

      for (s21_size_t i = 0; i < size_str; i++) {
        inserted[start_index + i] = str[i];
      }

      for (s21_size_t i = start_index; i < size_src; i++) {
        inserted[start_index + size_str + (i - start_index)] = src[i];
      }
    }
  }
  return (void *)inserted;
}
