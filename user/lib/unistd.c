#include "unistd.h"

isize syscall(
  usize id, 
  usize arg0, usize arg1, usize arg2
) {
  usize result;
  asm volatile (
    "mv a0, %2\n" // arg0
    "mv a1, %3\n" // arg1
    "mv a2, %4\n" // arg2
    "mv a7, %1\n" // which
    "ecall\n"
    "mv %0, a0\n" // ret
    : "=r"(result)
    : "r"(id), "r"(arg0), "r"(arg1), "r"(arg2)
    : "memory"
  );
  return result;
}

isize sys_write(
  usize fd, 
  const char *buf, 
  usize len
) {
  return syscall(
    SYSCALL_WRITE, 
    fd, (usize) buf, len
  );
}
