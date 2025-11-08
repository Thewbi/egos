# (C) 2024, Cornell University
# All rights reserved.

#prefix		= C:/SysGCC/risc-v/bin/riscv64-unknown-elf
#prefix 		= C:/Users/lapto/Downloads/xpack-riscv-none-elf-gcc-14.2.0-3-win32-x64/xpack-riscv-none-elf-gcc-14.2.0-3/bin/riscv-none-elf
prefix 		= riscv-none-elf

QEMU        = qemu-system-riscv32
RISCV_CC    = $(prefix)-gcc
OBJDUMP     = $(prefix)-objdump
OBJCOPY     = $(prefix)-objcopy

# https://stackoverflow.com/questions/46661932/gnu-mcu-eclipse-riscv-linker-error
# add -lgloss
LDFLAGS     = -nostdlib -lc -lgcc -lgloss
CFLAGS      = -march=rv32ima_zicsr -mabi=ilp32 -Wl,--gc-sections -ffunction-sections -fdata-sections -fdiagnostics-show-option -fno-builtin
DEBUG_FLAGS = --source --all-headers --demangle --line-numbers --wide

all:
	@printf "$(YELLOW)-------- Compile Hello, World! --------$(END)\n"
	$(RISCV_CC) $(CFLAGS) hello.s hello.c -Thello.lds $(LDFLAGS) -o hello.elf
	$(OBJDUMP) $(DEBUG_FLAGS) hello.elf > hello.lst
	$(OBJCOPY) -O binary hello.elf hello.bin

qemu: all
	@printf "$(YELLOW)-------- Run Hello-World on QEMU --------$(END)\n"
	$(QEMU) -nographic -machine virt -smp 1 -bios hello.bin

clean:
	rm -f hello.bin hello.lst hello.elf
	rm -f thread.bin thread.lst thread.elf
	rm -rf build earth/kernel_entry.lds tools/mkfs tools/mkrom tools/qemu/egos.bin tools/disk.img tools/bootROM.bin

GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
END = \033[0m
