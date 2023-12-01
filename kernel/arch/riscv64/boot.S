.section .text,"ax",%progbits 
.global pkx_entry
pkx_entry:
  la sp, boot_stack_top
  call pkx_start

  .section .bss.stack
  .globl boot_stack_lower_bound
boot_stack_lower_bound:
  .space 4096 * 16
  .globl boot_stack_top
boot_stack_top:

# for link app
.section .data
.global app_1_start
.global app_1_end
app_1_start:
  .incbin "../../build/user/riscv64/app1.bin"
app_1_end:
.global app_2_start
.global app_2_end
app_2_start:
  .incbin "../../build/user/riscv64/app2.bin"
app_2_end:
.global app_3_start
.global app_3_end
app_3_start:
  .incbin "../../build/user/riscv64/app3.bin"
app_3_end:
