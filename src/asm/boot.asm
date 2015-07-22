; boot.asm
;
; Copyright (C) 2015 Noah Sandman
; All rights reserved.
;
; This software may be modified and distributed under the terms
; of the BSD license.  See the LICENSE file for details.
;

bits 64

global _start
extern kmain

section .text
	_start:
		cli				; Halt interrupts
		call kmain
		hlt