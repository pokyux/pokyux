#include "pkx_call.h"
#include "task.h"
#include "stdio.h"

#include "./system.h"

void pkx_sys_exit(usize exit_code) {
  pkx_printk("App finished.\n");
  pkx_get_task(pkx_get_running_tid())->status = PKX_TASK_EXITED;
  pkx_next_task(pkx_get_running_tid());
}

isize pkx_sys_yield() {
  pkx_task *prev = pkx_get_task(pkx_get_running_tid());
  prev->status = PKX_TASK_READY;
  pkx_next_task(prev->tid);
}
