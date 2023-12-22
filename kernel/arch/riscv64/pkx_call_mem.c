#define PKX_PHYS_MEM_START 0x80200000
#define PKX_PHYS_MEM_END   0x80800000 // not included

// pokyux 在 RISCV64 上使用 SV39 地址结构
// SV39: Phys: 44 PPN + 12 offset
//       Virt: 27 VPN + 12 offset

struct _pkx_ppn_manager {
  usize start, end;         // end is not included
  u8 allocation_table[192]; // caculate all avail phys mem
} pkx_ppn_manager;

void pkx_init_mem(u8 *kernel_start, u8 *kernel_end);
usize pkx_alloc_ppn();
void pkx_free_ppn();
usize pkx_addr_to_ppn(void *_addr);
void *pkx_ppn_to_addr(usize ppn);
