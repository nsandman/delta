#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

uint8_t inb (uint16_t);
void outb (uint16_t, uint8_t);

#ifndef NULL
#	define NULL ((void*)0)
#endif

#endif
