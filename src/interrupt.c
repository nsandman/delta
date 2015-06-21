#include <interrupt.h>

const char *exceptions[] = {
	"Division by zero",
	"Debug",
	"Non-maskable interrupt",	
	"Breakpoint",
	"Into detected overflow",
	"Out of bounds",
	"Invalid opcode",
	"No coprocessor",
	"Double fault",
	"coprocessor segment overrun",
	"Bad TSS",
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Unknown interrupt",
	"Coprocessor fault",
	"Alignment check",
	"Machine check"
};

void isr_handler(registers_t regs) {
	printf("Got interrupt %d (%s)!\n",regs.int_no,regs.int_no<18)?exceptions[regs.int_no]:"Reserved";
	for(;;)
		__asm__("hlt");
}