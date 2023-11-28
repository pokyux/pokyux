#include "type.h"
#include "pkx_call.h"
#include "stdio.h"

usize pkx_start() {
  pkx_printk("%s %d\n", "Pokyux kernel started.", 233);
  while (true) pkx_idle();
}
