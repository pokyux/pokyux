#include "type.h"
#include "pkx_call.h"
#include "stdio.h"

usize pkx_start() {
  pkx_printk("Pokyux kernel started.\n");
  while (true) pkx_idle();
}
