#ifndef PKX_PROCESS_H
#define PKX_PROCESS_H

#include "type.h"
#include "memory.h"
#include "stdio.h"

#define PKX_MAX_PROCESS_NUM 128
#define PKX_USER_STACK_SIZE 4096*2
#define PKX_KERNEL_STACK_SIZE 4096*2

typedef struct {
  usize pid;
  void *addr;
  void *kernel_stack;
  void *user_stack;
} pkx_process;

static pkx_process *pkx_process_list[PKX_MAX_PROCESS_NUM];

void pkx_init_process();
void pkx_next_process();
u8 *pkx_push_stack(u8 *sp, u8 *content, usize len);

#endif
