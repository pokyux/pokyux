#include "process.h"
#include "pkx_call.h"
#include "stdio.h"

void pkx_init_process() {
  for (usize i = 0; i < PKX_MAX_PROCESS_NUM; i++)
    pkx_process_list[i] = nullptr;
  pkx_printk("Process controler init ok.\n");
}

void pkx_next_process() {
  // tmp impl
  pkx_idle();
}

u8 *pkx_push_stack(u8 *sp, u8 *content, usize len) {
  sp -= len;
  for (usize i = 0; i < len; i++)
    sp[i] = content[i];
  return sp;
}
