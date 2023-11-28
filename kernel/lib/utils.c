#include "utils.h"
#include "pkx_call.h"

char pkx_hex_map[] = {
  '0', '1', '2', '3',
  '4', '5', '6', '7',
  '8', '9', 'A', 'B',
  'C', 'D', 'E', 'F'
};

void pkx_print_hex(usize hex) {
#ifdef PKX32
  usize len = 8;
#else
  usize len = 16;
#endif
  while (len--) {
    usize cphex = hex;
    for (usize i = 0; i < len; i++)
      cphex >>= 4;
    pkx_putchar(pkx_hex_map[((u8) cphex) & 0x0F]);
  }
}
