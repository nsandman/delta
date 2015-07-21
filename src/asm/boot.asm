; boot.asm
;
; Copyright (C) 2015 Noah Sandman
; All rights reserved.
;
; This software may be modified and distributed under the terms
; of the BSD license.  See the LICENSE file for details.
;

bits 64

global start
extern kmain

section .text
	start:
		cli				; Halt interrupts
		call kmain
		hlt