#include "app.h"
#include "pkx_call.h"
#include "stdio.h"

bool pkx_load_app_bin(usize addr, usize len) {
  pkx_printk("Loading app from addr: 0x%x, size: 0d%d\n", addr, len);
  pkx_memcpy((u8*) 0x80400000, (u8*) addr, len);
  pkx_fresh_icache();
}

void pkx_next_app() {
  // tmp impl
  pkx_idle();
}

void pkx_push_stack(u8 *sp, u8 *content, usize len) {
  sp -= len;
  for (usize i = 0; i < len; i++)
    sp[i] = content[i];
}
