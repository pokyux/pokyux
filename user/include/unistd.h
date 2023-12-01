#include "type.h"

#define STDOUT 1

#define SYSCALL_WRITE  64
#define SYSCALL_EXIT   93
#define SYSCALL_YIELD 124

isize syscall(
  usize id, 
  usize arg0, usize arg1, usize arg2
);

isize sys_write(
  usize fd, 
  const char *buf, 
  usize len
);
