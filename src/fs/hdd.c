#include <hdd.h>

extern void ata_lba_read();

/*
 * Rather than screw with the stack directly, I
 * figured I would just use readsector as an abstraction.
 * ata_lba_read (from hdd.asm) takes three parameters: 
 *
 * rdi: the buffer address. The data is written to this location.
 * cl : number of sectors to read.
 * eax: the LBA of the sector you want to read.
 */
void 
readsector(uint32_t lba, uint8_t nsect, uint64_t addr)
{
	// The assembly just moves the paramters into place...
	__asm(
		"mov %0, %%rdi\n"
		"mov %1, %%cl\n"
		"mov %2, %%eax\n" : :
		"r"(addr), "r"(nsect), "r"(lba)
	);
	ata_lba_read(); // ...and then calls the function. I could
					// have done this in assembly ("call ata_lba_read"),
					// but what's the point? This is clearer and 
					// generates the same assembly.
}