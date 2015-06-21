#include <screen.h>

#define DELTA_VERSION 10292
#define P64_VERS	  "0.6.1"

int kmain() {
	cls();
	printf("Welcome to Delta v%d \"Alfalfa\", loaded by Pure64 v%s!\n\n", DELTA_VERSION, P64_VERS);
	printf("System specs: \nCPUS: %dx @ %dmHZ\n", *((uint16_t*)0x5014), *((uint16_t*)0x5010));
	printf("RAM:  %dMiB\nVid:  0x%x", *((uint16_t*)0x5020), *(uint32_t*)0x5040);
	idt_init();
	return 0xdea1;
}