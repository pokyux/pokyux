#include "sbi.h"

usize sbi_call(usize which, usize arg0, usize arg1, usize arg2) {
  usize result;
  asm volatile (
    "mv a0, %2\n" // arg0
    "mv a1, %3\n" // arg1
    "mv a2, %4\n" // arg2
    "mv a7, %1\n" // which
    "ecall\n"
    "mv %0, a0\n" // ret
    : "=r"(result)
    : "r"(which), "r"(arg0), "r"(arg1), "r"(arg2)
    : "memory"
  );
  return result;
}

void pkx_putchar(char c) {
  sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}
