#include "pkx_call.h"
#include "process.h"
#include "stdio.h"

#include "./system.h"

void pkx_sys_exit(usize exit_code) {
  pkx_printk("App finished.\n");
  pkx_next_process();
}
