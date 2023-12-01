#include "type.h"

// call for M mode service
void pkx_putchar(char c);
void pkx_puts(char *str);
void pkx_idle();
void pkx_fresh_icache();
void pkx_shutdown();
void pkx_panic(const char *info);

// call from U mode
void pkx_init_trap();

// asm abstract
void pkx_launch_task(u8 *addr, u8 *kernel_stack, u8 *user_stack);
