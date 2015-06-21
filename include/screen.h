#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <system.h>
#include <string_functions.h>

int cursorX = 0, cursorY = 0;
const uint8_t sw = 80,sh = 25,sd = 2;                                                     //We define the screen width, height, and depth.

void clearLine(uint8_t from,uint8_t to) {
	uint16_t i = sw * from * sd;
	char* vidmem=(char*)0xb8000;
	for(;i<(sw*(to+1)*sd);i++, vidmem++)
		*vidmem = 0x0;
}

void updateCursor() {
	unsigned temp = cursorY * sw + cursorX;  // Position = (y * width) +  x
	outb(0x3D4, 14);              // CRT Control Register: Select Cursor Location
	outb(0x3D5, temp >> 8);       // Send the high byte across the bus
	outb(0x3D4, 15);              // CRT Control Register: Select Send Low byte
	outb(0x3D5, temp);            // Send the Low byte of the cursor location
}

void cls() {
	clearLine(0,sh-1);
	cursorX = 0;
	cursorY = 0;
	updateCursor();
}

void scrollUp(uint8_t lineNumber) {
	char* vidmem = (char*)0xb8000;
	uint16_t i = 0;
	for (i;i<sw*(sh-1)*sd;i++)
		vidmem[i] = vidmem[i+sw*sd*lineNumber];
	clearLine(sh-1-lineNumber,sh-1);
	if((cursorY - lineNumber) < 0 ) {
		cursorY = 0;
		cursorX = 0;
	} else 
		cursorY -= lineNumber;
	updateCursor();
}


void newLineCheck() {
	if(cursorY >=sh-1)
		scrollUp(1);
}

void putchar(char c) {
	char* vidmem = (char*)0xb8000;     
	switch(c) {
		case 0x08:
			if(cursorX > 0) 
			{
				cursorX--;									
				vidmem[(cursorY * sw + cursorX)*sd]=0x00;	                              
			}
			break;
		case 0x09:    
			cursorX = (cursorX + 8) & ~(8 - 1); 
			break;
		case '\r':
			cursorX = 0;
			break;
		case '\n':
			cursorX = 0;
			cursorY++;
			break;
		default:
			vidmem [((cursorY * sw + cursorX))*sd] = c;
			vidmem [((cursorY * sw + cursorX))*sd+1] = 0x0F;
			cursorX++; 
			break;
	}
	if(cursorX >= sw) {
		cursorX = 0;
		cursorY++;
	}
	newLineCheck();
	updateCursor();
}

void puts(const char* data) {
	for (; *data != '\0'; data++)
		putchar(*data);
}

#endif
