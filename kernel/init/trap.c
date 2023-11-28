#include "trap.h"
#include "pkx_call.h"

void pkx_trap_handler() {
  pkx_before_trap();
  pkx_after_trap();
}
