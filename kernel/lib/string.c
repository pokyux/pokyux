#include "type.h"

#include "./string.h"

usize pkx_strlen(const char *str) {
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

char *pkx_itoa(isize i) {
  return nullptr;
  // if (i == 0)
  //   return "0";
  // usize digit = 0;
  // bool neg = false;

  // if (i < 0) {
  //   i = -i;
  //   neg = true;
  //   digit++;
  // }

  // isize cpi = i;
  // while (cpi) {
  //   digit++;
  //   cpi /= 10;
  // }

  // char *ret = (char*) malloc(sizeof(char)*(digit+1));
  // usize cur = 0;
  // while (i) {
  //   ret[cur++] = i%10+'0';
  //   i /= 10;
  // }
  // if (neg)
  //   ret[cur++] = '-';
  // ret[cur] = 0;
  // pkx_strrev(ret);
  // return ret;
}
