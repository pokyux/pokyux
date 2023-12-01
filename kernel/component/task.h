#ifndef PKX_task_H
#define PKX_task_H

#include "type.h"
#include "memory.h"
#include "stdio.h"

#define PKX_MAX_TASK_NUM 128
#define PKX_USER_STACK_SIZE 4096*2
#define PKX_KERNEL_STACK_SIZE 4096*2

#define PKX_TASK_UNINIT  0
#define PKX_TASK_READY   1
#define PKX_TASK_RUNNING 2
#define PKX_TASK_EXITED  3

typedef struct {
  usize ra, sp;
  usize s[12];
} pkx_task_context;

typedef struct {
  usize tid;
  usize status;
  void *addr;
  usize size;
  void *kernel_stack;
  void *user_stack;
  pkx_task_context context;
} pkx_task;

void pkx_init_task();
void pkx_next_task(usize except_tid);
void pkx_add_task(void *addr, usize size);
pkx_task pkx_get_task(usize tid);
usize pkx_get_running_tid();
void pkx_set_running_tid(usize tid);
u8 *pkx_push_stack(u8 *sp, u8 *content, usize len);

#endif
