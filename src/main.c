#include <screen.h>
#include <io.h>
#include <interrupt.h>

#define DELTA_VERSION 13276

int kmain() {
	idt_init();
	vid_init();
	printf("Delta v%d \"Absinthe\"\n\n", DELTA_VERSION);
	char *c = malloc(3);
	char *d = malloc(46);
	printf("c: %p\nd: %p\n", c, d);
	free(d);
	char *e = malloc(8);
	printf("e: %p", e);
	return 0xdea1;
}