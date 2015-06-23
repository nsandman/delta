#include <screen.h>
#include <io.h>
#include <interrupt.h>

#define DELTA_VERSION 13276

int kmain() {
	vid_init();
	printf("Delta v%d \"Absinthe\"\n\n", DELTA_VERSION);
	puts("Initializing the interrupt descriptor table... ");
	idt_init();
	cputs("OK.\n", 0x00ff00);
	return 0xdea1;
}