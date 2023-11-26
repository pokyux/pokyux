#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "./test.h"
#include "type.h"
#include "./string.h"

void test_string() {
  char *str = "hello pkx";
  checkeq(pkx_strlen(str), strlen(str));
  checkeq(pkx_strlen("123"), 3);
}

usize main(usize argc, char **argv) {
  test_unit tests[] = {
    {"string", test_string}
  };

  int test_num = sizeof(tests) / sizeof(test_unit);
  u8 *need_test = (u8*) malloc(sizeof(u8)*test_num);
  for (usize i = 0; i < test_num; i++)
    need_test[i] = (argc == 1);

  for (usize i = 0; i < test_num; i++) {
    if (!need_test[i]) continue;
    printf("Testing %s...\n", tests[i].test_name);
    tests[i].test_func();
    printf("Test %s passed.\n\n", tests[i].test_name);
  }

  free(need_test);
  return 0;
}
