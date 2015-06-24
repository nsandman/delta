include config.local

ASM := $(shell which nasm)
QMU := $(shell which qemu-system-x86_64)
GCC := $(shell which $(TOOLPREFIX)gcc)

CFL = -c -ffreestanding -finline-functions \
-Iinclude -nostdlib -std=c99 -fno-stack-protector -mno-red-zone
OUT = out/main.o out/interrupt_asm.o out/system.o out/interrupt.o \
out/strings.o out/screen.o out/idt.o out/io.o

all: out out/bmfs_mbr.sys out/pure64.sys out/boot_asm.o $(OUT) out/kernel.sys out/delta.image

# Instead of running the provided "build.sh"
include contrib/pure64/build.make

out:
	mkdir -p out/

# So if we change any headers, main.c will get recompiled
out/main.o: src/main.c include/*.h
	$(GCC) $(CFL) -o$@ $<

out/%_asm.o: src/%.asm
	$(ASM) -felf64 -o$@ $<

out/%.o: src/%.c
	$(GCC) $(CFL) -o$@ $<

out/kernel.sys: $(OUT)
	$(GCC) -nostdlib -lgcc -static-libgcc -Tlink.ld $^ -o$@

out/delta.image: out/bmfs_mbr.sys out/pure64.sys out/kernel.sys
	bmfs $@ initialize 6M $^

clean:
	rm -rf out

qemu: all
	$(QMU) -smp 2 -hda out/delta.image -name "Delta"