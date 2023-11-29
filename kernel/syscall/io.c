#include "stdio.h"
#include "pkx_call.h"

#include "./io.h"

#define PKX_STDOUT 1

isize pkx_sys_write(usize fd, const char *buf, usize len) {
  if (fd != PKX_STDOUT) {
    pkx_printk("Unknown fd. Syscall canceled.\n");
    return 0;
  }

  for (usize i = 0; i < len; i++)
    pkx_putchar(buf[i]);
  return len;
}
