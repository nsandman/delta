#include <screen.h>
#include <io.h>
#include <interrupt.h>

#define DELTA_VERSION 13276

int kmain() {
	idt_init();
	vid_init();
	printf("Delta v%d \"Absinthe\"\n\n", DELTA_VERSION);
	return 0xdea1;
}