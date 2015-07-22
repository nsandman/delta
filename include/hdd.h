#ifndef _HDD_
#define _HDD_

#include <stdint.h>

// To make stuff feel less weird
typedef uint8_t  byte;
typedef uint16_t word;
typedef uint32_t dword;
typedef uint64_t qword;

void readsector(uint32_t, uint8_t, uint64_t);

#endif