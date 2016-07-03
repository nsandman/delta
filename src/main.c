/* main.c -- Delta's kmain()
 *
 * Copyright (C) 2015 Noah Sandman
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license.  See the LICENSE file for details.
 */

#include <io.h>
#include <hdd.h>
#include <screen.h>
#include <interrupt.h>

#define DELTA_VERSION 393276
#define DEBUG_ADDR    0x200000c

extern uint32_t kernel_end;		// Declared in link.ld

int 
kmain()
{
	idt_init();
	vid_init();
	printf("Delta v%d \"Absinthe\"\n\n", DELTA_VERSION);
	readsector(0, 1, DEBUG_ADDR);
	int *hddtest;
	*hddtest = DEBUG_ADDR;
	printf("0x%x\n", hddtest);
	puts("if you can see this, at least it's not hanging.");
	return 0xdea1;
}