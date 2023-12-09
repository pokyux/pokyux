#include "type.h"

typedef struct {
  usize x[32];
  usize sstatus;
  usize sepc;
  usize kernel_stack;
  usize user_stack;
} pkx_trap_context;
