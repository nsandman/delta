global read_lba_sector

; This is meant to be called from C code, so its 
; arguments are passed on the stack.

; This code is mostly based on the example given
; at http://wiki.osdev.org/ATA_read/write_sectors.
read_lba_sector:
	; Get arguments from the stack.
	pop rdi
	pop rcx
	pop rax

	; LBA is now in rbx
	mov rbx, rax

	; Port to which bit 24-27 of LBA
	; and drive are sent.
	mov edx, 0x01F6
	shr eax, 24			; Get bits 24-27

	or al, 11100000b	; Enable LBA mode
	out dx, al			; Send al to port dx

	mov edx, 0x01F2		; Port that number of sectors goes to
	mov al, cl			; Move al to cl so we can use it with the "out" instruction
	out dx, al

	mov edx, 0x1F3		; Bits 0-7 of LBA port
	mov eax, ebx		; LBA is in bx

	mov edx, 0x1F4		; Bits 8-15 of LBA port
	mov eax, ebx
	shr eax, 8			; Only bits 8-15
	out dx, al

	mov edx, 0x1F5		; Bits 16-23 of LBA port
	mov eax, ebx
	shr eax, 16			; Just bits 16-23
	out dx, al

	mov edx, 0x1F7		; Command port (finally)
	mov al, 0x20
	out dx, al