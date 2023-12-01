#include "mem.h"

#define PKX_ALLOC_BASE_ADDR 0x80500000

void *pkx_alloc_top_addr;

void *pkx_alloc(usize size) {
  void *ret = pkx_alloc_top_addr;
  pkx_alloc_top_addr += size;
}

void *pkx_free(void *addr) {
  // TODO: impl
}
