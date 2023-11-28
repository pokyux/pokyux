#include "type.h"
#include "pkx_call.h"
#include "stdio.h"

usize pkx_start() {
  extern void pkx_entry;
  pkx_printk("Pokyux kernel addr: %x\n", &pkx_entry);
  extern void app_hello_start;
  pkx_printk("App hello addr: %x\n", &app_hello_start);
  while (true) pkx_idle();
}
