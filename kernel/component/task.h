#ifndef PKX_task_H
#define PKX_task_H

#include "type.h"
#include "memory.h"
#include "stdio.h"

#define PKX_MAX_TASK_NUM 128
#define PKX_USER_STACK_SIZE 4096*2
#define PKX_KERNEL_STACK_SIZE 4096*2

typedef struct {
  usize pid;
  void *addr;
  usize size;
  void *kernel_stack;
  void *user_stack;
} pkx_task;

void pkx_init_task();
void pkx_next_task();
void pkx_add_task(void *addr, usize size);
pkx_task pkx_get_task(usize pid);
u8 *pkx_push_stack(u8 *sp, u8 *content, usize len);

#endif
