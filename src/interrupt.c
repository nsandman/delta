#include <interrupt.h>

void isr_handler(registers_t regs) {
	printf("Got interrupt $%d!", regs.int_no);
	for(;;)
		__asm__("hlt");
}