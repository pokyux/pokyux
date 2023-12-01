#include "unistd.h"
#include "stdlib.h"
#include "string.h"

int main() {
  char str[] = "hello from user 3!\n";
  int sl = strlen(str);
  sys_write(STDOUT, str, sl);
  exit(0);
}
