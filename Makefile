ASM := $(shell which nasm)
QMU := $(shell which qemu-system-x86_64)
GCC := $(shell which gcc)
LNK := $(shell which ld)

CFL = -c -ffreestanding -Wno-implicit-function-declaration -finline-functions \
-Iinclude -nostdlib -std=c99 -fno-stack-protector -mno-red-zone
OUT = out/main.o out/interrupt_asm.o out/interrupt.o out/idt.o out/io.o

all: out out/delta/bmfs_mbr.sys out/delta/pure64.sys out/boot_asm.o $(OUT) out/delta/kernel.sys out/delta.image

# Instead of running the provided "build.sh"
include contrib/pure64/Makefile

out:
	mkdir -p out/delta/

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

qemu: out/delta.image
	$(QMU) -hda $< -name "Delta"