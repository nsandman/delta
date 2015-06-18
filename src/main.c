#include <screen.h>

int kmain() {
	cls();
	/*
	For some reason, this works...
		putchar('W');
		putchar('e');
		putchar('l');
		putchar('c');
		putchar('o');
		putchar('m');
		putchar('e');
		putchar(' ');
		putchar('t');
		putchar('o');
		putchar(' ');
		putchar('d');
		putchar('e');
		putchar('l');
		putchar('t');
		putchar('a');
		putchar('!');

	But this doesn't!
		puts("Welcome to delta!");
	*/
	return 0xdea1;
}