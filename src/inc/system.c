#include <system.h>
#include <stringf.h>
#include <io.h>

uint32_t heap_cs = HEAP_IN_SZ;	// Current heap size

uint8_t inb (uint16_t _port) {
	uint8_t rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

void outb (uint16_t _port, uint8_t _data) {
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

/* 
 * Now here comes the good stuff.
 * Basically, everything that has no category (read: malloc)
 * goes here. Since I'm not implementing libc, I don't need
 * a stdlib.h (and that would be confusing anyway since we're not using
 * -nostdinc).
 */

// Think sbrk(), but without all the sbrk(0) weirdness when calling it.
// This is much simpler because it just returns a pointer to your new memory.
void *extend_heap(intptr_t sz) {
	size_t heapinc = (uint64_t)sz+sizeof(block_meta_t);
	if (heap_cs + heapinc > HEAP_MAX)						// Don't let the heap get bigger than HEAP_MAX
		return NULL;
	void *block = (void*)HEAP_START+heap_cs;		// Pointer to sz bytes after heap end
	heap_cs += heapinc;	
	return block;		// Block is the end of the allocated memory, so return the beginning of it
}

// Round up to the nearest power of two. Pretty self-explanatory.
size_t __2pow_rndup(size_t num) {
	size_t i = 1;
	while (i < num)
		i *= 2;
	return i;
}

// The first and last entries in our linked list
block_meta_t *malloc_last = NULL, *malloc_first = NULL;

// An array of free blocks and their header addresses.
block_meta_t *free_blocks[256];
uint8_t free_block_index = 0;	// The place to add the next free block.

block_meta_t *find_free_block(size_t size) {
	for (uint8_t i = 0; i < free_block_index; i++)
		if (free_blocks[i]->size==size && free_blocks[i]->isfree) { // Just in case
			block_meta_t *r = free_blocks[i];
			free_blocks[i] = (block_meta_t*)0;
			return r;
		}
	return NULL;
}

void set_vals(size_t size, block_meta_t** ptr) {
	block_meta_t *p2;
	p2->size   = size;
	p2->next   = NULL;
	p2->isfree = 0;
	*ptr = &p2;
} 

// Delta's kernel-space implementation of malloc() is partially based
// off info from http://www.danluu.com.
void *malloc(size_t sz) {
	if (sz) {
		sz = __2pow_rndup(sz);
		block_meta_t *previous = malloc_last;

		// I know this *shouldn't* be a double pointer, but for some reason
		// it doesn't write to the struct when I set values if it's a single.
		block_meta_t **ptr     = extend_heap(sz);
		if (!ptr)	// If both of those operations failed, return a null pointer.
			return NULL;
		if (malloc_last) {
			malloc_last  = previous->next = *ptr;
		} else {
			malloc_first = malloc_last = *ptr;
		}
		// The setting of the values is screwing up the print function :/
		set_vals(sz, ptr);
		return (*ptr)+1;
	}
	return NULL;
}

void *calloc(size_t nmemb, size_t size) {
	size_t sz = size*nmemb;
	void *ret = malloc(sz);
	if (ret)
		memset(&ret, 0, sz);
	return ret;
}

void free(void *ptr) {
	if (ptr) {
		block_meta_t *block = (block_meta_t*)ptr-1;
		//printf("\nfree %d\n", block->size);
		printf("%d", block->size);
	}
}