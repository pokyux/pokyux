#include "syscall.h"

// syscall id: 124
isize sys_yield() {
  syscall(124, 0, 0, 0);
}
