#include "type.h"

#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93

isize syscall(
  usize id, 
  usize arg0, usize arg1, usize arg2
);

isize sys_write(
  usize fd, 
  const char *buf, 
  usize len
);