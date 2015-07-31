#include <io.h>
#include <hdd.h>
#include <stdint.h>

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
		"mov %0, %%rdi;"
		"mov %1, %%cl;"
		"mov %2, %%eax;" 
		"call ata_lba_read;"
		: : "m"(addr), "m"(nsect), "m"(lba)
		: "rdi", "cl", "eax"	
	);
}