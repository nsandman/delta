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
		"mov %2, %%eax;" : :
		"r"(addr), "r"(nsect), "r"(lba)
	);
	ata_lba_read(); // ...and then calls the function. I could
					// have done this in assembly ("call ata_lba_read"),
					// but what's the point? This is clearer and 
					// generates the same assembly.
}

void
get_params(hdd_info_t *block)
{
	// This function assumes the result buffer looks like
	// THIS: en.wikipedia.org/wiki/INT_13H#INT_13h_AH.3D48h:_Extended_Read_Drive_Parameters
	// and starts at address 0x5068.
	block->spt = *(uint32_t*)0x5074;							// Offset 0x0c
	//block->hpc = (*(uint32_t*)0x5070)/(*(uint32_t*)0x506C);		// Number of heads/number of cylinders
	printf("%d\n", block->spt);
}