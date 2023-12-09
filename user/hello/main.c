#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "not_posix.h"

int main() {
  char str[] = "App0: Before sys yield\n";
  int sl = strlen(str);
  sys_write(STDOUT, str, sl);
  sys_yield();
  char str1[] = "App0: After sys yield\n";
  sl = strlen(str1);
  sys_write(STDOUT, str1, sl);
  exit(0);
}
