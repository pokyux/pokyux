/* linker script from rcore */

OUTPUT_ARCH(riscv)
ENTRY(pkx_entry)

BASE_ADDRESS = 0x80200000;

SECTIONS
{
  . = BASE_ADDRESS;
  .text : {
    *(.text.pkx_entry)
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
