#include "task.h"
#include "pkx_call.h"
#include "stdio.h"
#include "mem.h"

static pkx_task pkx_task_list[PKX_MAX_TASK_NUM];
usize pkx_task_num, pkx_task_running;

void pkx_init_task() {
  pkx_task_num = 0;
  pkx_task_running = -1;
  pkx_printk("task controler init ok.\n");
}

void pkx_next_task(usize prev_tid) {
  extern void pkx_switch_task(task_context *ts, task_context *td);
  for (usize i = 0; i < pkx_task_num; i++) {
    if (pkx_task_list[i].tid == except_tid)
      continue;
    if (pkx_task_list[i].status == PKX_TASK_READY)
      pkx_switch_task(
        &pkx_task_list[prev_tid].context,
        &pkx_task_list[i].context
      );
  }
  pkx_panic("No task avail.\n");
}

u8 *pkx_push_stack(u8 *sp, u8 *content, usize len) {
  sp -= len;
  for (usize i = 0; i < len; i++)
    sp[i] = content[i];
  return sp;
}

void pkx_add_task(void *addr, usize size) {
  pkx_task_list[pkx_task_num].tid = pkx_task_num;
  pkx_task_list[pkx_task_num].status = PKX_TASK_UNINIT;
  pkx_task_list[pkx_task_num].addr = addr;
  pkx_task_list[pkx_task_num].size = size;
  pkx_task_list[pkx_task_num].kernel_stack
    = pkx_alloc(PKX_KERNEL_STACK_SIZE);
  pkx_task_list[pkx_task_num].user_stack
    = pkx_alloc(PKX_USER_STACK_SIZE);
  pkx_devide_line("Add task");
  pkx_printk("tid         : %d\n", pkx_task_num);
  pkx_printk("Addr        : %x\n", addr);
  pkx_printk("Size        : %x\n", size);
  pkx_printk("Kernel Stack: %x\n", pkx_task_list[pkx_task_num].kernel_stack);
  pkx_printk("User   Stack: %x\n", pkx_task_list[pkx_task_num].user_stack);
  pkx_task_list[pkx_task_num].status = PKX_TASK_READY;
  pkx_task_num++;
}

pkx_task pkx_get_task(usize tid) {
  return pkx_task_list[tid];
}

usize pkx_get_running_tid() {
  return pkx_task_running;
}

void pkx_set_running_tid(usize tid) {
  pkx_task_running = tid;
}
