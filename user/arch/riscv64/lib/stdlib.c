#include "unistd.h"

void exit(isize exit_code) {
  syscall(SYSCALL_EXIT, (usize) exit_code, 0, 0);
}
