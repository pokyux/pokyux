#define PKX_PHYS_MEM_START 0x80200000
#define PKX_PHYS_MEM_END   0x80800000 // not included

void pkx_init_mem(u8 *kernel_start, u8 *kernel_end);
void *pkx_alloc(usize size);
void pkx_free(void *addr);