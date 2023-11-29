#include "type.h"

#define PKX_SYSCALL_WRITE 64
#define PKX_SYSCALL_EXIT  93

usize pkx_syscall(
  usize id, 
  usize arg0, usize arg1, usize arg2
);
