#include "trap_context.h"
#include "stdio.h"
#include "type.h"
#include "pkx_arch.h"
#include "task.h"
#include "memory.h"

// read from RISCV manual
// https://people.eecs.berkeley.edu/~krste/papers/riscv-privileged-v1.9.pdf
#define PKX_RV64_INSTRUCTION_ACCESS_FAULT 0x1
#define PKX_RV64_ECALL 0x8

pkx_trap_context *pkx_trap_handler(
  pkx_trap_context *context
) {
  pkx_devide_line("Trap");
  usize scause, stval;
  asm volatile (
    "csrr %0, scause\n"
    "csrr %1, stval\n"
    : "=r"(scause) ,"=r"(stval)
    ::
  );

  usize tid = pkx_get_running_tid();

  switch (scause) {
    case PKX_RV64_INSTRUCTION_ACCESS_FAULT:
      pkx_printk("instruction access fault, stval: %x\n", stval);
      pkx_next_task(tid);
      break;
    case PKX_RV64_ECALL:
      context->sepc += 4;
      context->x[10] = pkx_syscall(
        context->x[17], 
        context->x[10], context->x[11], context->x[12]
      );
      break;
    default:
      pkx_printk("Unknown trap id: %d\n", scause);
      pkx_printk("App failed. Load another.\n");
      pkx_next_task(tid);
  }
  return context;
}
