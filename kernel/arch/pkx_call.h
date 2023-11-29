#include "type.h"

// call for M mode service
void pkx_putchar(char c);
void pkx_puts(char *str);
void pkx_idle();
void pkx_fresh_icache();
void pkx_shutdown();

// call from U mode
void pkx_init_trap();

// asm abstract
void pkx_launch_app(usize addr);
