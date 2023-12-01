#include "process.h"
#include "pkx_call.h"
#include "stdio.h"
#include "mem.h"

static pkx_process pkx_process_list[PKX_MAX_PROCESS_NUM];
usize pkx_process_num;

void pkx_init_process() {
  pkx_process_num = 0;
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

void pkx_add_process(void *addr, usize size) {
  pkx_process_list[pkx_process_num].pid = pkx_process_num;
  pkx_process_list[pkx_process_num].addr = addr;
  pkx_process_list[pkx_process_num].size = size;
  pkx_process_list[pkx_process_num].kernel_stack
    = pkx_alloc(PKX_KERNEL_STACK_SIZE);
  pkx_process_list[pkx_process_num].user_stack
    = pkx_alloc(PKX_USER_STACK_SIZE);
  pkx_devide_line("Add Process");
  pkx_printk("Pid         : %d\n", pkx_process_num);
  pkx_printk("Addr        : %x\n", addr);
  pkx_printk("Size        : %x\n", size);
  pkx_printk("Kernel Stack: %x\n", pkx_process_list[pkx_process_num].kernel_stack);
  pkx_printk("User   Stack: %x\n", pkx_process_list[pkx_process_num].user_stack);
  pkx_process_num++;
}

pkx_process pkx_get_process(usize pid) {
  return pkx_process_list[pid];
}
