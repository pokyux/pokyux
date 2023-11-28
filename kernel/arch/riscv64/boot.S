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
.global app_hello_start
.global app_hello_end
app_hello_start:
  .incbin "../../build/user/riscv64/hello.bin"
app_hello_end:
