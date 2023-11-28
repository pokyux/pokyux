#include "pkx_call.h"
#include "sbi.h"
#include "string.h"

void pkx_putchar(char c) {
  sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}

void pkx_puts(char *str) {
  usize l = pkx_strlen(str);
  for (usize i = 0; i < l; i++)
    pkx_putchar(str[i]);
}

void pkx_idle() {
  asm("wfi");
}

void pkx_fresh_icache() {
  asm volatile ("fence.i");
}
