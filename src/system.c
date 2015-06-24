#include <system.h>
#include <stringf.h>

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
	size_t heapsize = heap_cs+(uint64_t)sz;
	if (heapsize > HEAP_MAX)						// Don't let the heap get bigger than HEAP_MAX
		return NULL;
	void *block = (void*)(HEAP_START+heapsize);		// Pointer to sz bytes after heap end
	heap_cs += (uint32_t)sz;	
	return block-sz;		// Block is the end of the allocated memory, so return the beginning of it
}

// Round up to the nearest power of two. Pretty self-explanatory.
static size_t __2pow_rndup(size_t num) {
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

static block_meta_t *find_free_block(size_t size) {
	for (uint8_t i = 0; i < free_block_index; i++)
		if (free_blocks[i]->size==size && free_blocks[i]->isfree) // Just in case
			return free_blocks[i];
	return NULL;
}

// Delta's implementation of malloc() is partially based
// off info from http://www.danluu.com/malloc-tutorial.
void *malloc(size_t size) {
	if (!free_block_index)		// If free_blocks is already empty, null it out so there's no cruft
		memset(free_blocks, 0, sizeof(free_blocks));
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
			malloc_first = malloc_last;
			goto return_ptr;			// Yeah, goto came in handy. Go figure.
		}
		return_ptr:
			malloc_last=ptr;
			ptr->magic=0xff;
			ptr->isfree=0;
			ptr->size=size;
			ptr->next=NULL;
			return ptr+1; // We've been messing with the header this whole time... return the data AFTER it.
	}
	return NULL;		// If an error occurred, return a null pointer.
}

// This isn't technically standards-compliant, but... screw it.
void *calloc(size_t nmemb, size_t size) {
	size_t alloc_sz = size*nmemb;
	void *ptr = malloc(alloc_sz);
	if (ptr)
		memset(&ptr, 0, alloc_sz);
	return ptr;
}

void free(void *ptr) {
	/*
	if (!ptr)
		return;			// Exit if null pointer is passed
	block_meta_t *block_data = (block_meta_t*)(ptr-1);	// We want the block's header.
	if (block_data->isfree || block_data->magic != 0xff)
		puts("NO");
		return;				// Exit if the block is already freed or wrong magic number
	free_blocks[free_block_index++] = block_data;
	block_data->isfree=1;
	*/
	// Do nothing for now; we can't get the pointer's header. That's a problem.
}