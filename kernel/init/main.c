#include "type.h"
#include "pkx_call.h"
#include "stdio.h"
#include "process.h"

usize pkx_start() {
  pkx_init_trap();
  pkx_init_process();

  extern void pkx_entry;
  pkx_devide_line("Pokyux Start");
  pkx_printk("Kernel addr: %x\n", &pkx_entry);

  pkx_panic("Shouldn't reach here. End of pkx_start.");
}
