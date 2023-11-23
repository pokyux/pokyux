INCLUDES := -Ikernel -Ikernel/arch/riscv64
BUILD := build
PREFIX := riscv64-unknown-elf-
QEMU := qemu-system-riscv64

.SUFFIXES: .h .c .S
.DELETE_ON_ERROR:

build: FORCE
	-mkdir $(BUILD)
	$(PREFIX)gcc $(INCLUDES) \
		kernel/arch/riscv64/boot.S \
		kernel/arch/riscv64/*.c \
		kernel/init/*.c \
		-o $(BUILD)/pokyux.elf \
		-T kernel/linker.ld \
		-nostartfiles -nostdlib
	$(PREFIX)objcopy -O binary \
		$(BUILD)/pokyux.elf \
		$(BUILD)/pokyux.bin

run: build
	$(QEMU) --machine virt -nographic -bios default -device loader,file=$(BUILD)/pokyux.bin,addr=0x80200000

clean:
	rm -rf $(BUILD)/*

.PHONY: FORCE
FORCE: