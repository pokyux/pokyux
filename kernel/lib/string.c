#include "string.h"

usize pkx_strlen(char *str) {
  usize len = 0;
  while (str[len]) len++;
  return len;
}
