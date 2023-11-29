#include "type.h"
#include "memory.h"
#include "stdio.h"

typedef struct {
  usize app_num;
  usize current_running;
} pkx_app_manager;

bool pkx_load_app_bin(usize addr, usize len);
void pkx_next_app();
