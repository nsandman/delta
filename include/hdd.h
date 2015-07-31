#ifndef _HDD_
#define _HDD_

#include <stdint.h>

#define HDDBUF_SIZE 30			// Size of the HDD buffer gotten from "int 13h AH=48h"

// To make stuff feel less weird
typedef uint8_t  byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

// This has the info to convert from CHS to LBA:
// en.wikipedia.org/wiki/Logical_block_addressing#CHS_conversion
typedef struct {
	uint32_t hpc;		// heads per cylinder
	uint32_t spt;		// sectors per track
} hdd_info_t;

void readsector(uint32_t, uint8_t, uint64_t);

#endif