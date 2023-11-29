#include "type.h"
#include "memory.h"
#include "stdio.h"

typedef struct {
  usize app_num;
  usize current_running;
} pkx_app_manager;

#ifndef PKX_DEF_STACK
#define PKX_DEF_STACK
#define PKX_USER_STACK_SIZE 4096*2
static u8 pkx_user_stack[PKX_USER_STACK_SIZE];
#define PKX_KERNEL_STACK_SIZE 4096*2
static u8 pkx_kernel_stack[PKX_KERNEL_STACK_SIZE];
static u8 *pkx_kernel_sp;
#endif

void pkx_init_kernel_stack();
bool pkx_load_app_bin(usize addr, usize len);
void pkx_next_app();
void pkx_push_kernel_stack(u8 *content, usize len);
