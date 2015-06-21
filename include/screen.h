#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

// So all our functions have easy access to VBE data
// This info table is constructed by Pure64, and the
// way to see what data is where is on this webpage:
// ctyme.com/intr/rb-0274.htm
typedef struct vesa_important_stuff {
	uint16_t pitch;		// AKA "bytes per scanline", offset 0x10
	uint32_t lfb_addr;	// Linear frame buffer physical address, offset 0x28
	uint8_t  pixel_w;	// Pixel width. Divide bits per pixel (off. 0x19) by 8
	uint16_t height;	// Screen height. Pure64 finds this for us and puts it at 0x5044.
	uint16_t width;		// Screen width. Pure64 loads this at 0x5046.
	uint8_t  depth;		// Color depth. Size of red mask + blue mask + green mask?
} vbe_info_t;

vbe_info_t *vbe_block;
char       *vidmem;

// NOTE: This function isn't very well commented since info 
// on how to find anything, and what any particular variable
// is for is in the "struct vesa_important_stuff" code.
void init_vid() {
	// Non-VBE stuff first (Pure64 loads this for us)
	vbe_block->height   = *((uint16_t*)0x5044);
	vbe_block->width    = *((uint16_t*)0x5046);

	vbe_block->pitch    = *((uint16_t*)0x5c10);
	vbe_block->lfb_addr = *((uint32_t*)0x5c28);

	vbe_block->pixel_w  = ((*((uint8_t*)0x5c19))/8);
	vbe_block->depth    = (*(uint8_t*)0x5c1f)+(*(uint8_t*)0x5c21)+(*(uint8_t*)0x5c23);
	vidmem              = (char*)vbe_block->lfb_addr;	// Set the vidmem pointer to the LFB address
}

static void putpixel(unsigned char* screen, int x,int y, int color) {
    unsigned where = x*3 + y*2400;
    screen[where] = color & 255;              // BLUE
    screen[where + 1] = (color >> 8) & 255;   // GREEN
    screen[where + 2] = (color >> 16) & 255;  // RED
}

// The only original screen.h function that still works in VESA mode
/*
void puts(const char* data) {
	for (; *data != '\0'; data++)
		putchar(*data);
}
*/

#endif
