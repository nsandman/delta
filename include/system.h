#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stddef.h>

#define HEAP_START 0xc000000
#define HEAP_IN_SZ 0x00000	// Initial heap size
#define HEAP_MAX   1000000

typedef struct bmt {
	size_t size;
	struct bmt *next;
	uint8_t isfree;
	uint8_t magic;
} block_meta_t;

uint8_t inb (uint16_t);
void outb (uint16_t, uint8_t);

// Functions used internally by the malloc() family
void *extend_heap(intptr_t);	// Like sbrk(), but not really (see system.c)
size_t __2pow_rndup(size_t); // Round up to the nearest power of two
block_meta_t *find_free_block(size_t);	// Find free block with a certain size

// malloc() and friends
void *malloc(size_t);
void free(void*);

#endif
