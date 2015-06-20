bits 64

extern isr_handler

%macro ISR_E 1
	global isr%1
	isr%1:
		cli
		push byte 0
		push byte %1
		jmp isr_common_stub
%endmacro

%macro ISR_D 1
	global isr%1
	isr%1:
		cli
		push byte %1
		jmp isr_common_stub
%endmacro

ISR_E 0
ISR_E 1
ISR_E 2
ISR_E 3
ISR_E 4
ISR_E 5
ISR_E 6
ISR_E 7
ISR_D 8
ISR_E 9
ISR_D 10
ISR_D 11
ISR_D 12
ISR_D 13
ISR_D 14
ISR_E 15
ISR_E 16
ISR_E 17
ISR_E 18
ISR_E 19
ISR_E 20
ISR_E 21
ISR_E 22
ISR_E 23
ISR_E 24
ISR_E 25
ISR_E 26
ISR_E 27
ISR_E 28
ISR_E 29
ISR_E 30
ISR_E 31

isr_common_stub:
	push rdi
	push rsi
	push rbp
	push rsp
	push rbx
	push rdx
	push rcx
	push rax

	mov ax, ds
	push rax

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call isr_handler

	pop rax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	pop rdi
	pop rsi
	pop rbp
	pop rsp
	pop rbx
	pop rdx
	pop rcx
	pop rax
	add rsp, 8
	sti
	iretq