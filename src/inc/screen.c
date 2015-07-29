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
	uint32_t loc = (x*vbe_block->pixel_w)+(y*vbe_block->pitch);
	// This assembly does the same thing as the following C code:
	// vidmem[loc]   = color & 255;
	// vidmem[loc+1] = (color >> 8)  & 255;
	// vidmem[loc+2] = (color >> 16) & 255;
	__asm(
		"movl %0, %%edi;"
		"movl %k1, %%ebx;" 
		"addl %%ebx, %%edi;"
		"movl %2, %%eax;"
		"stosb;"
		"shrl $8, %%eax;"
		"stosw;" : :
		"m"(loc), "r"(vidmem), "m"(color)
	);
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

char* 
strcpy(char *strDest, const char *strSrc)
{
    if (strDest!=NULL || strSrc!=NULL)
    	return NULL;
    char *temp = strDest;
    while((*strDest++ = *strSrc++)); // or while((*strDest++=*strSrc++) != '\0');
    return temp;
}

// THESE are from Apple Open Source.
int
strncmp(const char *s1, const char *s2, size_t n)
{
    for ( ; n > 0; s1++, s2++, --n)
  if (*s1 != *s2)
      return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
  else if (*s1 == '\0')
      return 0;
    return 0;
}

char*
strchr(const char *s, int c)
{
    const char ch = c;

    for ( ; *s != ch; s++)
        if (*s == '\0')
            return 0;
    return (char *)s;
}

void 
cputs(const char *str, uint32_t color) 
{
	for (;*str!='\0';str++)
		cputchar(*str, color);
}
