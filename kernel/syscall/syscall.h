#include "type.h"

#define PKX_SYS_WRITE 64
#define PKX_SYS_EXIT  93
#define PKX_SYS_YIELD 124

isize pkx_syscall(
  usize id, 
  usize arg0, usize arg1, usize arg2
);
