#include "type.h"
#include "pkx_call.h"
#include "stdio.h"
#include "task.h"

usize pkx_start() {
  pkx_init_trap();
  pkx_init_mem();
  pkx_init_task();

  // for rcore ch3, load 4 apps
  extern void app_hello_start;
  extern void app_hello_end;
  usize app_hello_size = &app_hello_end - &app_hello_start;
  extern void app_1_start;
  extern void app_1_end;
  usize app_1_size = &app_1_end - &app_1_start;
  extern void app_2_start;
  extern void app_2_end;
  usize app_2_size = &app_2_end - &app_2_start;
  extern void app_3_start;
  extern void app_3_end;
  usize app_3_size = &app_3_end - &app_3_start;

  pkx_memcpy(0x80400000, &app_hello_start, app_hello_size);
  pkx_memcpy(0x80410000, &app_1_start, app_1_size);
  pkx_memcpy(0x80420000, &app_2_start, app_2_size);
  pkx_memcpy(0x80430000, &app_3_start, app_3_size);
  pkx_add_task(0x80400000, app_hello_size);
  pkx_add_task(0x80410000, app_1_size);
  pkx_add_task(0x80420000, app_2_size);
  pkx_add_task(0x80430000, app_3_size);
  pkx_printk("Load 4 apps ok.\n");

  for (usize i = 0; i < 4; i++)
    pkx_printk("Task %d, Status: %d\n", i, pkx_get_task(i)->status);

  pkx_task *now = pkx_get_task(1);
  pkx_continue_task(now);

  pkx_panic("Shouldn't reach here. End of pkx_start.");
}
