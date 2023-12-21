void pkx_init_mem(u8 *kernel_start, u8 *kernel_end);
void *pkx_alloc(usize size);
void pkx_free(void *addr);