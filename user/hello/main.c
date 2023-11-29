#include "unistd.h"
#include "stdlib.h"
#include "string.h"

int main() {
  char str[] = "hello from user!";
  int sl = strlen(str);
  sys_write(STDOUT, "hello from user!", sl);
  exit(0);
}
