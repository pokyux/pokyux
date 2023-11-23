#include "pkx_call.h"
#include "sbi.h"

void pkx_putchar(char c) {
  sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}
