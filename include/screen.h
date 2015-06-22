#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <notcouriersans/notcouriersans.h>	// This is the font. It's not courier sans.

// So all our functions have easy access to VBE data
// This info table is constructed by Pure64, and the
// way to see what data is where is on this webpage:
// ctyme.com/intr/rb-0274.htm
typedef struct {
	uint16_t pitch;		// AKA "bytes per scanline", offset 0x10
	uint32_t lfb_addr;	// Linear frame buffer physical address, offset 0x28
	uint8_t  pixel_w;	// Pixel width. Divide bits per pixel (off. 0x19) by 8
	uint16_t height;	// Screen height. Offset 0x14.
	uint16_t width;		// Screen width. Offset 0x12.
	uint8_t  depth;		// Color depth. Size of red mask + blue mask + green mask?
} vbe_info_t;

vbe_info_t *vbe_block;
uint8_t    *vidmem;

// NOTE: This function isn't very well commented since info 
// on how to find anything, and what any particular variable
// is for is in the "vbe_info_t" code.
void init_vid() {
	vbe_block->height   = *((uint16_t*)0x5c14);
	vbe_block->width    = *((uint16_t*)0x5c12);

	vbe_block->pitch    = *((uint16_t*)0x5c10);
	vbe_block->lfb_addr = *((uint32_t*)0x5c28);

	vbe_block->pixel_w  = ((*((uint8_t*)0x5c19))/8);
	vbe_block->depth    = (*(uint8_t*)0x5c1f)+(*(uint8_t*)0x5c21)+(*(uint8_t*)0x5c23);
	vidmem              = (uint8_t*)vbe_block->lfb_addr;	// Set the vidmem pointer to the LFB address
}

void putpixel(uint8_t* scrn, uint32_t x, uint32_t y, uint32_t color) {
    uint32_t loc  = (x*vbe_block->pixel_w)+(y*vbe_block->pitch);
    scrn[loc]     = color & 255;
    scrn[loc+1]   = (color >> 8) & 255;
    scrn[loc+2]   = (color >> 16) & 255;
}

// The only original screen.h function that still works in VESA mode
/*
void puts(const char* data) {
	for (; *data != '\0'; data++)
		putchar(*data);
}
*/

#endif
