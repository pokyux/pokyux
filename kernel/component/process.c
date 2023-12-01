#include "task.h"
#include "pkx_call.h"
#include "stdio.h"
#include "mem.h"

static pkx_task pkx_task_list[PKX_MAX_task_NUM];
usize pkx_task_num;

void pkx_init_task() {
  pkx_task_num = 0;
  pkx_printk("task controler init ok.\n");
}

void pkx_next_task() {
  // tmp impl
  pkx_idle();
}

u8 *pkx_push_stack(u8 *sp, u8 *content, usize len) {
  sp -= len;
  for (usize i = 0; i < len; i++)
    sp[i] = content[i];
  return sp;
}

void pkx_add_task(void *addr, usize size) {
  pkx_task_list[pkx_task_num].pid = pkx_task_num;
  pkx_task_list[pkx_task_num].addr = addr;
  pkx_task_list[pkx_task_num].size = size;
  pkx_task_list[pkx_task_num].kernel_stack
    = pkx_alloc(PKX_KERNEL_STACK_SIZE);
  pkx_task_list[pkx_task_num].user_stack
    = pkx_alloc(PKX_USER_STACK_SIZE);
  pkx_devide_line("Add task");
  pkx_printk("Pid         : %d\n", pkx_task_num);
  pkx_printk("Addr        : %x\n", addr);
  pkx_printk("Size        : %x\n", size);
  pkx_printk("Kernel Stack: %x\n", pkx_task_list[pkx_task_num].kernel_stack);
  pkx_printk("User   Stack: %x\n", pkx_task_list[pkx_task_num].user_stack);
  pkx_task_num++;
}

pkx_task pkx_get_task(usize pid) {
  return pkx_task_list[pid];
}
