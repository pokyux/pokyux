#include "mem.h"

#define PKX_ALLOC_BASE_ADDR 0x80500000

void *pkx_alloc_top_addr;

void pkx_init_mem() {
  pkx_alloc_top_addr = PKX_ALLOC_BASE_ADDR;
}

void *pkx_alloc(usize size) {
  void *ret = pkx_alloc_top_addr;
  pkx_alloc_top_addr += size;
  return ret;
}

void *pkx_free(void *addr) {
  // TODO: impl
}
