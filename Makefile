INCLUDES := -Ikernel -Ikernel/arch -Ikernel/lib
BUILD := build
PREFIX := $(ARCH)-unknown-elf-
QEMU := qemu-system-$(ARCH)

.SUFFIXES: .h .c .S
.DELETE_ON_ERROR:

build: FORCE
	-mkdir $(BUILD)
	-mkdir $(BUILD)/$(ARCH)
	$(PREFIX)gcc $(INCLUDES) \
	  -mcmodel=medany \
		kernel/arch/$(ARCH)/boot.S \
		kernel/arch/$(ARCH)/*.c \
		kernel/init/*.c \
		kernel/lib/*.c \
		-o $(BUILD)/$(ARCH)/pokyux.elf \
		-T kernel/linker.ld \
		-nostartfiles -nostdlib
	$(PREFIX)objcopy -O binary \
		$(BUILD)/$(ARCH)/pokyux.elf \
		$(BUILD)/$(ARCH)/pokyux.bin

run: build
	$(QEMU) --machine virt \
		-nographic \
		-bios tool/rustsbi-qemu.bin \
		-device loader,file=$(BUILD)/$(ARCH)/pokyux.bin,addr=0x80200000

clean:
	rm -rf $(BUILD)/$(ARCH)/*

.PHONY: FORCE
FORCE: