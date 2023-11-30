BUILD := ../build
ARCH := riscv64
PREFIX := riscv64-unknown-elf-

mkuserdir:
	-mkdir $(BUILD)
	-mkdir $(BUILD)/user
	-mkdir $(BUILD)/user/$(ARCH)

hello: mkuserdir
	$(PREFIX)gcc \
		-w \
	  -mcmodel=medany \
		-I include \
		-T arch/$(ARCH)/linker.ld \
		-nostartfiles \
		-nostdlib \
		arch/$(ARCH)/start.S \
		arch/$(ARCH)/lib/*.c \
		hello/*.c \
		-o $(BUILD)/user/$(ARCH)/hello.elf
	$(PREFIX)objcopy -O binary \
		$(BUILD)/user/$(ARCH)/hello.elf \
		$(BUILD)/user/$(ARCH)/hello.bin