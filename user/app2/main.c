#include "unistd.h"
#include "stdlib.h"
#include "string.h"

int main() {
  char str[] = "App2: hello\n";
  int sl = strlen(str);
  sys_write(STDOUT, str, sl);
  exit(0);
}
