INCLUDES := -Ikernel
BUILD := build
PREFIX := riscv64-unknown-elf-
QEMU := qemu-system-riscv64

.SUFFIXES: .h .c .S
.DELETE_ON_ERROR:

build: kernel/init/* kernel/arch/*
	-mkdir $(BUILD)
	$(PREFIX)gcc $(INCLUDES) \
		kernel/arch/riscv64/boot.S \
		kernel/init/main.c \
		-o $(BUILD)/pokyux.elf \
		-T kernel/linker.ld \
		-nostartfiles -nostdlib
	$(PREFIX)objcopy -O binary \
		$(BUILD)/pokyux.elf \
		$(BUILD)/pokyux.bin

run: build
	$(QEMU) --machine virt -nographic -bios default -device loader,file=$(BUILD)/pokyux.bin,addr=0x0

clean:
	rm -rf $(BUILD)/*
