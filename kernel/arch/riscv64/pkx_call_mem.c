#define PKX_PHYS_MEM_START 0x80200000
#define PKX_PHYS_MEM_END   0x80800000 // not included

struct _pkx_ppn_manager {
  usize start, end;         // end is not included
  u8 allocation_table[192]; // caculate all avail phys mem
} pkx_ppn_manager;

void pkx_init_mem(u8 *kernel_start, u8 *kernel_end);
usize pkx_alloc_ppn();
void pkx_free_ppn();
void *pkx_get_pp_addr(usize ppn);
