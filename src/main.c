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

extern uint32_t kernel_end;		// Declared in link.ld

int 
kmain()
{
	idt_init();
	vid_init();
	printf("Delta v%d \"Absinthe\"\n\n", DELTA_VERSION);
	//readsector(0, 1, DEBUG_ADDR);
	return 0xdea1;
}