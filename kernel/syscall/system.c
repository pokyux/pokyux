#include "pkx_call.h"
#include "app.h"

#include "./system.h"

void pkx_sys_exit(usize exit_code) {
  pkx_next_app();
}
