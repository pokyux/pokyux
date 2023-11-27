#ifdef PKX_TEST
#include <string.h>
#include <stdlib.h>

#include "type.h"
#include "./test.h"
#include "./string.h"
#include "./memory.h"

void test_string() {
  char str[] = "123";
  checkeq(pkx_strlen(str), strlen(str));
  checkeq(pkx_strlen("123"), 3);
  checkneq(pkx_strlen("123"), 4);

  check(pkx_strcmp("abc", "abc") == 0);
  check(pkx_strcmp("abc", "bbc") < 0);
  check(pkx_strcmp("bbc", "abc") > 0);

  pkx_strrev(str);
  checkeq(pkx_strcmp(str, "321"), 0);
  pkx_strrev(str);
  checkeq(pkx_strcmp(str, "123"), 0);

  checkeq(pkx_strcmp(pkx_itoa(0), "0"), 0);
  checkeq(pkx_strcmp(pkx_itoa(123), "123"), 0);
  checkeq(pkx_strcmp(pkx_itoa(4321), "4321"), 0);
}

void test_memory() {
  check(pkx_memcmp("abc123", "abc123", 7));
  check(!pkx_memcmp("abc123", "321cba", 7));
}

usize main(usize argc, char **argv) {
  test_unit tests[] = {
    {"string", test_string},
    {"memory", test_memory}
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

#endif
