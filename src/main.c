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

#define DELTA_VERSION 13276

extern uint32_t end;		// Declared in link.ld
uint32_t kernel_end;

// Initializes any non-constant data.
void
dat_init() 
{
	kernel_end = (uint32_t)&end;
}

int 
kmain()
{
	dat_init();
	idt_init();
	vid_init();
	printf("Delta v%d \"Absinthe\"\n\n", DELTA_VERSION);
	return 0xdea1;
}