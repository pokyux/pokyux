#include "pkx_call.h"
#define PKX_PHYS_MEM_START 0x80200000
#define PKX_PHYS_MEM_END   0x80800000 // not included

// pokyux 在 RISCV64 上使用 SV39 地址结构
// SV39: Phys: 44 PPN + 12 offset
//       Virt: 27 VPN + 12 offset

struct _pkx_ppn_manager {
  usize start, usable;      // start: 第一个物理页号, usable: 可用页面总数
  u8 allocation_table[192]; // bit map. 1 for avail, 0 for used.
} pkx_ppn_manager;

void pkx_init_mem(u8 *kernel_start, u8 *kernel_end) {
  usize start = pkx_addr_to_ppn(kernel_end) + 1;
  usize end   = pkx_addr_to_ppn(PKX_PHYS_MEM_END);
  pkx_ppn_manager.start  = start;
  pkx_ppn_manager.usable = end - start;
  // 目前 Pokyux 使用位图管理内存页，所以要求页面总数是 8 的倍数
  pkx_ppn_manager.usable -= pkx_ppn_manager % 8;
  usize bitmap_lenth = pkx_ppn_manager.usable / 8;

  if (bitmap_lenth > 192)
    pkx_panic("Phys mem too large.");
  if (bitmap_lenth <= 0)
    pkx_panic("No enough memory.");
  for (usize i = 0; i < bitmap_lenth; i++)
    pkx_ppn_manager.allocation_table[i] = 0xFF;
  
  pkx_devide_line("Init");
  pkx_printk("Mem init ok.\n");
  pkx_printk("Start PPN: 0x%x, Total PPN: d%d\n", start, pkx_ppn_manager.usable);
}

usize pkx_alloc_ppn();
void pkx_free_ppn();
usize pkx_addr_to_ppn(void *_addr);
void *pkx_ppn_to_addr(usize ppn);
