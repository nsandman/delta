#include <interrupt.h>

void isr_handler(registers_t regs) {
	printf("Got interrupt %u!", regs.int_no);
	for(;;)
		__asm__("hlt");
}