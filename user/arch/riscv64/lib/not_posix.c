#include "syscall.h"

// syscall id: 124
isize pkx_sys_yield() {
  syscall(124, 0, 0, 0);
}