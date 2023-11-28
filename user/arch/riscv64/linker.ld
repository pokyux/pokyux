/* linker script from kernel/arch/riscv64 */

OUTPUT_ARCH(riscv)
ENTRY(_start)

BASE_ADDRESS = 0x80400000;

SECTIONS
{
  . = BASE_ADDRESS;
  .text : {
    *(.text._start)
    *(.text .stub .text.* .gnu.linkonce.t.*)
  }

  PROVIDE(etext = .); 

  .rodata : {
    *(.rodata .rodata.* .gnu.linkonce.r.*)
  }

  . = ALIGN(0x1000);

  .data : {
    *(.data)
    *(.data.*)
  }
  .sdata : {
    *(.sdata)
    *(.sdata.*)
  }

  PROVIDE(edata = .);
  .bss : {
    *(.bss.stack)
    sbss = .;
    *(.bss .bss.*)
    *(.sbss .sbss.*)
  }
  ebss = .;

  PROVIDE(end = .);
  /DISCARD/ : {
    *(.eh_frame .note.GNU-stack)
  }
}
