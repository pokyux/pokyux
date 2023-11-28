#include "type.h"

bool pkx_memcmp(u8 *a, u8 *b, usize len) {
  for (usize i = 0; i < len; i++)
    if (a[i] != b[i])
      return false;
  return true;
}
