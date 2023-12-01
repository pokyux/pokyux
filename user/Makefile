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

app1: mkuserdir
	$(PREFIX)gcc -w -mcmodel=medany \
		-I include \
		-T app1/linker.ld \
		-nostartfiles \
		-nostdlib \
		arch/$(ARCH)/start.S \
		arch/$(ARCH)/lib/*.c \
		app1/*.c \
		-o $(BUILD)/user/$(ARCH)/app1.elf
	$(PREFIX)objcopy -O binary \
		$(BUILD)/user/$(ARCH)/app1.elf \
		$(BUILD)/user/$(ARCH)/app1.bin

app2: mkuserdir
	$(PREFIX)gcc -w -mcmodel=medany \
		-I include \
		-T app2/linker.ld \
		-nostartfiles \
		-nostdlib \
		arch/$(ARCH)/start.S \
		arch/$(ARCH)/lib/*.c \
		app2/*.c \
		-o $(BUILD)/user/$(ARCH)/app2.elf
	$(PREFIX)objcopy -O binary \
		$(BUILD)/user/$(ARCH)/app2.elf \
		$(BUILD)/user/$(ARCH)/app2.bin

app3: mkuserdir
	$(PREFIX)gcc -w -mcmodel=medany \
		-I include \
		-T app3/linker.ld \
		-nostartfiles \
		-nostdlib \
		arch/$(ARCH)/start.S \
		arch/$(ARCH)/lib/*.c \
		app3/*.c \
		-o $(BUILD)/user/$(ARCH)/app3.elf
	$(PREFIX)objcopy -O binary \
		$(BUILD)/user/$(ARCH)/app3.elf \
		$(BUILD)/user/$(ARCH)/app3.bin

app1-3: app1 app2 app3
