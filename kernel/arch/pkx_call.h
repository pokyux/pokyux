// call for M mode service
void pkx_putchar(char c);
void pkx_puts(char *str);
void pkx_idle();
void pkx_fresh_icache();

// call from U mode
void pkx_init_trap();
void pkx_before_trap();
void pkx_after_trap();
