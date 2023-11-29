#include "syscall.h"
#include "io.h"
#include "stdio.h"

usize pkx_syscall(
  usize id, 
  usize arg0, usize arg1, usize arg2
) {
  switch (id)
  {
  case PKX_SYS_WRITE:
    return pkx_sys_write(arg0, (char*) arg1, arg2);
  case PKX_SYS_EXIT:
    return pkx_sys_exit(arg0);
  default:
    pkx_printk("Error: Unknown syscall id: %d\n", id);
    return -1;
  }
}
