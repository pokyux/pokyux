#include "pkx_call.h"
#include "sbi.h"
#include "string.h"
#include "type.h"

#include "stdio.h"

void pkx_putchar(char c) {
  sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}

void pkx_puts(char *str) {
  usize l = pkx_strlen(str);
  for (usize i = 0; i < l; i++)
    pkx_putchar(str[i]);
}

void pkx_idle() {
  asm("wfi");
}

void pkx_fresh_icache() {
  // TODO: uncomment this asm before uploading to board
  // asm volatile ("fence.i");
}

void pkx_shutdown() {
  // tmp impl
  pkx_idle();
}

void pkx_init_trap() {
  extern void pkx_trap_vector;
  usize trap_vector_addr = &pkx_trap_vector;
  asm volatile (
    "csrw stvec, %0"
    :: "r"(trap_vector_addr):
  );

  // debug
  usize stvec;
  asm volatile (
    "csrr %0, stvec"
    : "=r"(stvec) ::
  );
  if (stvec == trap_vector_addr)
    pkx_printk("Trap init ok. stvec: %x\n", stvec);
  else
    pkx_printk("Trap init failed.\n");
}

void pkx_launch_app(usize addr) {
  asm volatile (
    "csrw sepc, %0\n"
    "sret"
    :: "r"(addr):
  );
}
