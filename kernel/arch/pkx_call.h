#include "type.h"
#include "task.h"

// call for M mode service
void pkx_putchar(char c);
void pkx_puts(char *str);

// asm abstract
void pkx_idle();
void pkx_fresh_icache();
void pkx_fresh_tlb();
void pkx_shutdown();
void pkx_panic(const char *info);

// arch & machine related
void  pkx_init_mem(u8 *kernel_start, u8 *kernel_end);
usize pkx_alloc_ppn();
void  pkx_free_ppn(usize ppn);
usize pkx_addr_to_ppn(void *_addr);
void *pkx_ppn_to_addr(usize ppn);
void  pkx_init_trap();
void  pkx_init_trap_context(pkx_task *task);
// void pkx_launch_task(pkx_task *task);
void pkx_continue_task(pkx_task *task);
