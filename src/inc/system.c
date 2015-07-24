#include <io.h>
#include <hdd.h>
#include <system.h>
#include <stringf.h>

uint32_t heap_cs = HEAP_IN_SZ;	// Current heap size

uint8_t 
inb(uint16_t _port) 
{
	uint8_t rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

void 
outb(uint16_t _port, uint8_t _data) 
{
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
void*
extend_heap(intptr_t sz) 
{
	size_t heapinc = (uint64_t)sz+sizeof(block_meta_t);
	if (heap_cs + heapinc > HEAP_MAX)						// Don't let the heap get bigger than HEAP_MAX
		return NULL;
	void *block = (void*)HEAP_START+heap_cs;		// Pointer to sz bytes after heap end
	heap_cs += heapinc;	
	return block;		// Block is the end of the allocated memory, so return the beginning of it
}

// Round up to the nearest power of two. Pretty self-explanatory.
size_t 
__2pow_rndup(size_t num) 
{
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

block_meta_t*
find_free_block(size_t size) 
{
	for (uint8_t i = 0; i < free_block_index; i++)
		if (free_blocks[i]->size==size && free_blocks[i]->isfree) { // Just in case
			block_meta_t *r = free_blocks[i];
			free_blocks[i] = (block_meta_t*)0;
			free_block_index--;
			return r;
		}
	return NULL;
}

// Delta's kernel-space implementation of malloc() is partially based
// off info from http://www.danluu.com.
void*
malloc(size_t size) 
{
	size = __2pow_rndup(size);
	block_meta_t *ptr;
	// If a suitable free block isn't found, extend the heap
	if (!(ptr = find_free_block(size)))
		ptr = extend_heap(size+sizeof(block_meta_t));
	// If BOTH of those didn't fail (ptr isn't null)
	if (ptr) {
		if (malloc_last) {	// If this isn't the first time malloc() was run
			malloc_last->next=ptr;		// Make the last linked list entry point to ptr
		} else {
			memset(&free_blocks, 0, sizeof(free_blocks));
			malloc_first = malloc_last;
			goto return_ptr;			// Yeah, goto came in handy. Go figure.
		}
		return_ptr:
			malloc_last=ptr;
			ptr->isfree=0;
			ptr->size=size;
			ptr->next=NULL;
			return ptr+1; // We've been messing with the header this whole time... return the data AFTER it.
	}
	return NULL;		// If an error occurred, return a null pointer.
}

void 
free(void *ptr) 
{
	if (!ptr)
		return;			// Exit if null pointer is passed
	block_meta_t *block_data = (block_meta_t*)ptr-1;	// We want the block's header.
	if (block_data->isfree)
		return;				// Exit if the block is already freed
	free_blocks[free_block_index++] = block_data;
	// If the next block is free, merge
	if (block_data->next && block_data->next->isfree) {
		block_data->size += block_data->next->size + sizeof(block_meta_t);
		block_data->next  = block_data->next->next;
	}
	block_data->isfree=1;
}