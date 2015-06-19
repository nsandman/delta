bits 64

global start
extern kmain

section .text
	start:
		cli				; Halt interrupts
		call kmain
		hlt