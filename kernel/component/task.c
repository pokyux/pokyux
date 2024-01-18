#include "task.h"
#include "pkx_call.h"
#include "stdio.h"

static pkx_task pkx_task_list[PKX_MAX_TASK_NUM];
usize pkx_task_num, pkx_task_running;

void pkx_init_task() {
  pkx_task_num = 0;
  pkx_task_running = -1;
  pkx_printk("pkx_task_running: %x\n", &pkx_task_running);
  pkx_printk("task controler init ok.\n");
}

void pkx_next_task(usize prev_tid) {
  if (prev_tid > pkx_task_num)
    pkx_panic("Invalid prev tid in pkx_next_task.");
  for (usize i = 0; i < pkx_task_num; i++) {
    if (pkx_task_list[i].tid == prev_tid)
      continue;
    if (pkx_task_list[i].status == PKX_TASK_READY) {
      pkx_printk("From tid[%d] switch to tid[%d]\n", prev_tid, i);
      pkx_continue_task(&pkx_task_list[i]);
    }
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
    = pkx_ppn_to_addr(pkx_alloc_ppn());
  pkx_task_list[pkx_task_num].user_stack
    = pkx_ppn_to_addr(pkx_alloc_ppn());
  pkx_init_trap_context(&pkx_task_list[pkx_task_num]);
  pkx_task_list[pkx_task_num].status = PKX_TASK_READY;
  pkx_task_num++;
}

pkx_task *pkx_get_task(usize tid) {
  return &pkx_task_list[tid];
}

usize pkx_get_running_tid() {
  return pkx_task_running;
}

void pkx_set_running_tid(usize tid) {
  pkx_task_running = tid;
}
