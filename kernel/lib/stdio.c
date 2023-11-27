#include "type.h"
#include "pkx_call.h"

#include "./stdio.h"
#include "./stdarg.h"
#include "./string.h"

isize get_place_holder(
  const char *fmt, usize fmtl, usize now
) {
  if (now >= fmtl) return -1;
  if (fmt[now++] != '%') return -1;
  while (now < fmtl) {
    if (fmt[now] == 'd'
      || fmt[now] == 's'
    ) return now;
    now++;
  }
  return -1;
}

void pkx_printf(const char *fmt, ...) {
  pkx_puts(fmt);
  // va_list ap;
  // va_start(ap, fmt);
  // usize l = pkx_strlen(fmt), cur = 0;
  // while (cur < l) {
  //   if (fmt[cur] != '%') {
  //     pkx_putchar(fmt[cur++]);
  //     continue;
  //   }

  //   char type_index = get_place_holder(fmt, l, cur);
  //   if (type_index == -1)
  //     return;
  //   switch (fmt[type_index]) {
  //     case 's':
  //       pkx_puts(va_arg(ap, char*));
  //       break;
  //     case 'd':
  //       char *tmpstr = pkx_itoa(va_arg(ap, i32));
  //       pkx_puts(tmpstr);
  //       free(tmpstr);
  //       break;
  //     default:
  //       break;
  //   }
  //   cur = type_index+1;
  // }
}

void pkx_printk(const char *fmt, ...) {
  pkx_puts("[kernel] ");
  pkx_puts(fmt);
}
