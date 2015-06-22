#include <screen.h>

// NOTE: This function isn't very well commented since info 
// on how to find anything, and what any particular variable
// is for is in screen.h.
void init_vid() {
        vbe_block->width    = *((uint16_t*)0x5c12);
        vbe_block->height   = *((uint16_t*)0x5c14);

        vbe_block->pitch    = *((uint16_t*)0x5c10);
        vbe_block->lfb_addr = *((uint32_t*)0x5c28);

        vbe_block->pixel_w  = ((*((uint8_t*)0x5c19))/8);
        vbe_block->depth    = (*(uint8_t*)0x5c1f)+(*(uint8_t*)0x5c21)+(*(uint8_t*)0x5c23);
        vidmem              = (uint8_t*)vbe_block->lfb_addr;    // Set the vidmem pointer to the LFB address
}

void putpixel(uint32_t x, uint32_t y, uint32_t color) {
    uint32_t loc    = (x*vbe_block->pixel_w)+(y*vbe_block->pitch);
    vidmem[loc]     = color & 255;
    vidmem[loc+1]   = (color >> 8) & 255;
    vidmem[loc+2]   = (color >> 16) & 255;
}

void putchar(char c) {
        uint32_t startx = global_x, starty = global_y;  // Set local X and Y to emulated cursor
        uint32_t char_idx = (c-CHAR_OFFSET)*CHAR_SIZE;          // Each array character in the array is 36 bytes
        for (uint8_t a = 0; a < CHAR_SIZE; a++) {
                for (uint8_t b = 8; b > 0; b--) {                       // Loop through each bit
                        if (((CURR_FONT[char_idx+a]>>b)&1)) 
                                putpixel(startx, starty, 0xffffff);             // If it's 1, start a pixel
                        if (!(a%2)) startx++;
                }
                startx=global_x;
                starty++;
        }
        global_x += starty/4;
}

// The only original screen.h function that still works in VESA mode
void puts(const char* data) {
        for (; *data != '\0'; data++)
                putchar(*data);
}