#include "pkx_call.h"
#define PKX_PHYS_MEM_START 0x80200000
#define PKX_PHYS_MEM_END   0x80800000 // not included

// pokyux 在 RISCV64 上使用 SV39 地址结构
// SV39: Phys: 44 PPN + 12 offset
//       Virt: 27 VPN + 12 offset

struct _pkx_ppn_manager {
  usize start, usable, allocation_table_lenth;      // start: 第一个物理页号, usable: 可用页面总数
  u8 allocation_table[192]; // bit map. 1 for avail, 0 for used.
} pkx_ppn_manager;

void pkx_init_mem(u8 *kernel_start, u8 *kernel_end) {
  usize start = pkx_addr_to_ppn(kernel_end) + 1;
  usize end   = pkx_addr_to_ppn(PKX_PHYS_MEM_END);
  pkx_ppn_manager.start  = start;
  pkx_ppn_manager.usable = end - start;
  // 目前 Pokyux 使用位图管理内存页，所以要求页面总数是 8 的倍数
  pkx_ppn_manager.usable -= pkx_ppn_manager.usable % 8;
  usize bitmap_lenth = pkx_ppn_manager.usable / 8;
  pkx_ppn_manager.allocation_table_lenth = bitmap_lenth;

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

u8 pkx_bit_selector[8] = {
  1 << 0,
  1 << 1,
  1 << 2,
  1 << 3,
  1 << 4,
  1 << 5,
  1 << 6,
  1 << 7
};

usize pkx_alloc_ppn() {
  usize i = 0;
  for (; i < pkx_ppn_manager.allocation_table_lenth; i++)
    if (pkx_ppn_manager.allocation_table[i])
      break;
  if (i == pkx_ppn_manager.allocation_table_lenth)
    return 0;
  for (usize j = 0; j < 8; j++) {
    if (pkx_ppn_manager.allocation_table[i] & pkx_bit_selector[j]) {
      pkx_ppn_manager.allocation_table[i] &= ~(pkx_bit_selector[j]);
      return pkx_ppn_manager.start + i * 8 + j;
    }
  }
  return 0;
}

void pkx_free_ppn(usize ppn) {
  if (ppn < pkx_ppn_manager.start)
    return;
  usize bitmap_location = (ppn - pkx_ppn_manager.start) / 8;
  usize in_bit_offset   = (ppn - pkx_ppn_manager.start) % 8;
  if (bitmap_location >= pkx_ppn_manager.allocation_table_lenth)
    return;
  pkx_ppn_manager.allocation_table[bitmap_location] |= pkx_bit_selector[in_bit_offset];
}

usize pkx_addr_to_ppn(void *_addr) {
  usize addr = (usize) _addr;
  return addr >> 12;
}

void *pkx_ppn_to_addr(usize ppn) {
  return (void *) (ppn << 12);
}

// PageTable & VirtPage

typedef usize pkx_pte;

enum pkx_pte_flag {
  v = 1 << 0,
  r = 1 << 1,
  w = 1 << 2,
  x = 1 << 3,
  u = 1 << 4,
  g = 1 << 5,
  a = 1 << 6,
  d = 1 << 7
};

pkx_pte pkx_make_pte(usize ppn, u8 flags) {
  return (pkx_pte) (ppn << 8 | ((pkx_pte) flags));
}

void pkx_fresh_tlb() {
  asm volatile ("sfence.vma");
}
