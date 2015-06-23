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
	cputs("\nGot interrupt ", 0xff0000);
	printf("%d",regs.int_no);
	cputs(" (", 0xff0000);
	cputs(regs.int_no<18?exceptions[regs.int_no]:"Reserved", 0xff0000);
	cputs(")!", 0xff0000);
	for(;;) __asm__("hlt");
}