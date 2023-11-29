#include "type.h"

bool pkx_memcmp(u8 *a, u8 *b, usize len);
bool pkx_memcpy(u8 *dst, const u8 *src, usize len);
void memcpy(void *dst, const void *src, usize len);
void pkx_memset(u8 *a, u8 val, usize len);
