#include "syscall.h"
#include "io.h"
#include "stdio.h"

isize pkx_syscall(
  usize id, 
  usize arg0, usize arg1, usize arg2
) {
  switch (id) {
  case PKX_SYS_WRITE:
    pkx_printk("syscall: PKX_SYS_WRITE\n");
    return pkx_sys_write(arg0, (char*) arg1, arg2);
  case PKX_SYS_EXIT:
    pkx_printk("syscall: PKX_SYS_EXIT\n");
    return pkx_sys_exit(arg0);
  case PKX_SYS_YIELD:
    pkx_printk("syscall: PKX_SYS_YIELD\n");
    return pkx_sys_yield();
  default:
    pkx_printk("Error: Unknown syscall id: %d\n", id);
    return -1;
  }
}
