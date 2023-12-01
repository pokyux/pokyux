#include "pkx_call.h"
#include "sbi.h"
#include "string.h"
#include "type.h"
#include "trap_context.h"
#include "task.h"

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

void pkx_panic(const char *info) {
  pkx_devide_line("Panic");
  pkx_printk("%s\n", info);
  pkx_shutdown();
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
    pkx_panic("Trap init failed.");
}

// pkx launch app 通过 trap restore 实现了启动功能
// 启动用户程序要实现的三步：
// 1. 设置 PC 跳转（传入用户程序加载到内存的地址）
// 2. 设置用户态
// 3. 准备用户和内核栈（开辟一块空间，传入低地址即可）
// 在 trap.S/restore 中设置好 sepc, 使得 CPU 在执行
//  sret 之后 跳转到用户程序地址
// 在 trap.S/restore 中设置好 sstatus 的 SPP 位
//  来控制 sret 之后程序运行在用户态
// 在 trap.S/restore 中将 x2 复制到 sscratch，然后
//  在 sret 前将 sscratch 与 sp (此时为内核栈) 对调
//  实现了内核栈切换到用户栈的动作
void pkx_launch_task(pkx_task *task) {
  pkx_devide_line("Launch App");
  pkx_printk("Launching app at : %x\n", task->addr);
  pkx_printk("Kernel stack addr: %x\n", task->kernel_stack);
  pkx_printk("User stack addr  : %x\n", task->user_stack);
  pkx_trap_context context;
  for (usize i = 0; i < 32; i++)
    context.x[i] = 0;
  asm volatile (
    "csrr %0, sstatus"
    : "=r"(context.sstatus)::
  );
  // set SPP to 0
  // ref: https://people.eecs.berkeley.edu/~krste/papers/riscv-privileged-v1.9.pdf
  // "SPP is set to 0 if the trap originated from user mode"
  // SSP: 8th bit from right to left
  context.sstatus &= (usize) 0xFFFFFEFF;
  context.sepc = task->addr;
  // set user sp. 
  // user sp is copied to sscratch, 
  //   and switched to sp in trap.S::pkx_trap_restore
  context.x[2] = task->user_stack + PKX_USER_STACK_SIZE;
  // 初始化应用程序的内核栈
  u8 *kernel_stack = PKX_KERNEL_STACK_SIZE + task->kernel_stack;
  // 将数据推入内核栈，在 trap.S 中使用这些数据，启动程序
  kernel_stack = pkx_push_stack(kernel_stack, &context, sizeof(context));

  task->status = PKX_TASK_RUNNING;

  extern void pkx_trap_restore(u8 *kernel_sp);
  pkx_trap_restore(kernel_stack);
  pkx_panic("Shouldn't reach here (End of launch app).");
}

void pkx_from_asm() {
  pkx_printk("From asm.\n");
}
