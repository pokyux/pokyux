#include "app.h"
#include "pkx_call.h"

bool pkx_load_app_bin(usize addr, usize len) {
  pkx_printk("Loading app from addr: 0x%x, size: 0d%d\n", addr, len);
  pkx_memcpy((u8*) 0x80400000, (u8*) addr, len);
  pkx_fresh_icache();
}
