#include "./string.h"

usize pkx_strlen(char *str) {
  usize len = 0;
  while (str[len]) len++;
  return len;
}

usize pkx_strcmp(char *a, char *b) {
  usize la = pkx_strlen(a);
  usize lb = pkx_strlen(b);
  usize cur = 0;
  while (cur < la && cur < lb) {
    if (a[cur] != b[cur])
      return a[cur] - b[cur];
    cur++;
  }
  return 0;
}

usize pkx_strrev(char *str) {
  usize start = 0, end = pkx_strlen(str)-1;
  while (start < end) {
    char tmp = str[start];
    str[start] = str[end];
    str[end] = tmp;
    start++; end--;
  }
}
