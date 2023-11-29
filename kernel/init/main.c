#include "type.h"
#include "pkx_call.h"
#include "stdio.h"
#include "app.h"

usize pkx_start() {
  pkx_init_trap();

  extern void pkx_entry;
  pkx_devide_line("Pokyux Start");
  pkx_printk("Kernel addr: %x\n", &pkx_entry);
  extern void app_hello_start;
  extern void app_hello_end;
  usize app_start = (usize) &app_hello_start;
  usize app_len = (usize) &app_hello_end - app_start;
  pkx_load_app_bin(app_start, app_len);

  // launch hello
  pkx_launch_app(0x80400000, pkx_kernel_stack, pkx_user_stack);

  while (true) pkx_idle();
}
