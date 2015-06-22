#include <screen.h>

#define DELTA_VERSION 10292

int kmain() {
	//cls();
	//	putpixel(vidmem, ((*(uint16_t*)0x5044)/2), ((*(uint16_t*)0x5046)/2), 0xff0000);
	/*
	printf("Delta v%d \"Alfalfa\"\n\n", DELTA_VERSION);
	printf("System Info:\n    General:\n        CPUS: %dx @ %dmHZ\n", *((uint16_t*)0x5014), *((uint16_t*)0x5010));
	printf("        RAM:  %dMiB\n", *((uint16_t*)0x5020));
	printf("    VESA:\n        Width:  %d\n        Height: %d\n", *((uint16_t*)0x5044), *((uint16_t*)0x5046));
	printf("        Pitch:  %d\n        LFB:    %p", *((uint16_t*)0x5C10), *((uint32_t*)0x5C28));
	*/
	init_vid();
	putpixel(vidmem, (vbe_block->width-1)/2, (vbe_block->height-1)/2, 0xffffff);
	//putchar('a');
	//idt_init();
	return 0xdea1;
}