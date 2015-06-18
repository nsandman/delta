bits 64

global start
extern kmain

section .text
	start:
		cli
		call kmain
		hlt