bits 64

global	strlen
strlen:
	push	rdi
	sub	rcx, rcx
	mov	rdi, [rsp+8]
	not	rcx
	sub	al, al
	cld
repne	scasb
	not	rcx
	pop	rdi
	lea	rax, [rcx-1]
	ret
