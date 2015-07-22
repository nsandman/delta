#include <screen.h>
#include <vcr_osd_mono/vom.h>

// NOTE: This function isn't very well commented since info 
// on how to find anything, and what any particular variable
// is for is in screen.h.
void 
vid_init() 
{
	vbe_block->pitch    = *((uint16_t*)0x5c10);
	vbe_block->lfb_addr = *((uint32_t*)0x5c28);
	vbe_block->pixel_w  = *((uint8_t*)0x5c19)/8;
	vbe_block->height   = *((uint16_t*)0x5c14);
	vbe_block->width    = *((uint16_t*)0x5c12);
	vbe_block->depth    = *(uint8_t*)0x5c1f + *(uint8_t*)0x5c21 + *(uint8_t*)0x5c23;
	vidmem              = (uint8_t*)vbe_block->lfb_addr;    // Set the global vidmem pointer to the LFB address
}

// Simulated "cursor" positions
uint32_t global_x = 0, global_y = 0;

// Color in 0xRRGGBB format
void 
putpixel(uint32_t x, uint32_t y, uint32_t color) 
{
	uint32_t loc    = (x*vbe_block->pixel_w)+(y*vbe_block->pitch);
	vidmem[loc]     = color & 255;
	vidmem[loc+1]   = (color >> 8)  & 255;
	vidmem[loc+2]   = (color >> 16) & 255;
}

void 
cputchar(char c, uint32_t color) 
{
	uint32_t startx = global_x, starty = global_y;  // Set local X and Y to emulated cursor
	switch (c) {
		case '\n':
			global_y += CF_STYLES.GlyphHeight;
			global_x = 0;
			break;
		case '\r':
			global_x = 0;
			break;
		default:
			{
				uint32_t char_idx = ((c-CHAR_OFFSET)*CHAR_SIZE);          // Each array character in the array is 36 bytes
				int loc = startx*vbe_block->pixel_w;
				for (uint8_t a = 0; a < CHAR_SIZE; a+=2) {					 // Loop through each byte
					for (uint8_t b = 15; b != 0; b--) {                       // Loop through each bit of that byte
						if ((CURR_FONT[char_idx+((b<7)?(a+1):a)])>>((b>6)?(b-7):b)&1)
							putpixel(startx, starty, color);
						loc += vbe_block->pitch;										 // Each row is 2 bytes
						startx++;
					}
					startx = global_x;
					starty++;
				}
				global_x += CF_STYLES.FixedWidth;
				// If the line can't fit one more character, add font height to global_y
				if (global_x + CF_STYLES.FixedWidth >= vbe_block->width) {
					global_y += CF_STYLES.GlyphHeight;
					global_x = 0;
				}
			}
			break;
	}
}

// The only original screen.h function that still works in VESA mode
void 
puts(const char* data) 
{
	for (;*data!='\0';data++)
		putchar(*data);
}

void 
cputs(const char *str, uint32_t color) 
{
	for (;*str!='\0';str++)
		cputchar(*str, color);
}