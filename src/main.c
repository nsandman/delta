#include <screen.h>

int kmain() {
	cls();
	puts("Welcome to Delta!\n");
	idt_init();
	puts("Nothing has frozen, so... good job, I guess.");
	return 0xdea1;
}