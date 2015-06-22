include config.local

ASM := $(shell which nasm)
QMU := $(shell which qemu-system-x86_64)
GCC := $(shell which $(TOOLPREFIX)gcc)
LNK := $(shell which $(TOOLPREFIX)ld)

CFL = -c -ffreestanding -Wno-implicit-function-declaration -finline-functions \
-Iinclude -nostdlib -std=c99 -fno-stack-protector -mno-red-zone
OUT = out/main.o out/interrupt_asm.o out/system.o out/interrupt.o string_asm.o out/screen.o out/idt.o out/io.o

all: out out/delta/bmfs_mbr.sys out/delta/pure64.sys out/boot_asm.o $(OUT) out/delta/kernel.sys out/delta.image

# Instead of running the provided "build.sh"
include contrib/pure64/Makefile

out:
	mkdir -p out/delta/

# So if we change any headers, main.c will get recompiled
out/main.o: src/main.c include/*.h
	$(GCC) $(CFL) -o$@ $<

out/%_asm.o: src/%.asm
	$(ASM) -felf64 -o$@ $<

out/%.o: src/%.c
	$(GCC) $(CFL) -o$@ $<

out/delta/kernel.sys: $(OUT)
	$(LNK) -Tlink.ld $^ -o$@

out/delta.image: out/delta/bmfs_mbr.sys out/delta/pure64.sys out/delta/kernel.sys
	bmfs $@ initialize 6M $^

clean:
	rm -rf out

qemu: all
	$(QMU) -smp 2 -hda out/delta.image -name "Delta"