#include "type.h"
#include "task.h"

// call for M mode service
void pkx_putchar(char c);
void pkx_puts(char *str);

// asm abstract
void pkx_idle();
void pkx_fresh_icache();
void pkx_shutdown();
void pkx_panic(const char *info);

// arch & machine related
void pkx_init_trap();
void pkx_init_trap_context(pkx_task *task);
void pkx_init_mem(u8 *kernel_start, u8 *kernel_end);
void *pkx_alloc(usize size);
void pkx_free(void *addr);
// void pkx_launch_task(pkx_task *task);
void pkx_continue_task(pkx_task *task);
