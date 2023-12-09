ARCH := riscv64
BUILD := build
DEFINE := 

PREFIX := $(ARCH)-unknown-elf-
QEMU := qemu-system-$(ARCH)
INCLUDES := -Ikernel \
	-Ikernel/arch \
	-Ikernel/lib \
	-Ikernel/component \
	-Ikernel/syscall

.SUFFIXES: .h .c .S
.DELETE_ON_ERROR:

build: FORCE
	-mkdir $(BUILD)
	-mkdir $(BUILD)/$(ARCH)
	$(PREFIX)gcc $(INCLUDES) \
		-w $(DEFINE)\
	  -mcmodel=medany \
		kernel/arch/$(ARCH)/*.S \
		kernel/arch/$(ARCH)/*.c \
		kernel/init/*.c \
		kernel/lib/*.c \
		kernel/syscall/*.c \
		kernel/component/*.c \
		-o $(BUILD)/$(ARCH)/pokyux.elf \
		-T kernel/arch/$(ARCH)/linker.ld \
		-nostartfiles -nostdlib
	$(PREFIX)objcopy -O binary \
		$(BUILD)/$(ARCH)/pokyux.elf \
		$(BUILD)/$(ARCH)/pokyux.bin

run: build
	$(QEMU) --machine virt \
		-nographic \
		-bios tool/rustsbi-qemu.bin \
		-device loader,file=$(BUILD)/$(ARCH)/pokyux.bin,addr=0x80200000

test: FORCE
	-mkdir build
	-mkdir build/test
	gcc $(INCLUDES) -DPKX_TEST\
		kernel/lib/*.c \
		-o build/test/test.elf
	./build/test/test.elf

clean:
	rm -rf $(BUILD)/$(ARCH)/*

.PHONY: FORCE
FORCE:
