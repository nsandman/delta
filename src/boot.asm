bits 64

global start
extern kmain

start:
	cli
	call kmain
	hlt