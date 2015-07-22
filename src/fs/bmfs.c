/* Reads a BareMetal filesystem-formatted volume.
   Also probably the simplest filesystem to use as
   a template for any future kernel FSes.       */

#include <hdd.h>
#include <vfs.h>
#include <bmfs.h>
#include <stringf.h>

/*
 * github.com/ReturnInfinity/BMFS/wiki/BareMetal-File-System
 *
 * Block 0:
 *   4KiB - Legacy MBR Boot sector (512B)
 *   Free space (3584B)
 *   4KiB - Directory (Max 64 files, 64-bytes for each record)
 *   Free space (2040KiB)
 *
 * Block 1 .. n-1: 
 *    Data
 *
 * Block n (last block on disk): 
 *    Copy of Block 0
 */

bmfs_volume_t*
bmfs_getvolume(int lba, uint64_t buffer_addr)
{
	bmfs_volume_t *vol = NULL;
	vol->start = lba;			// The volume starts at LBA "lba"

	// Check for a copy of the 512-byte boot sector. Then we know
	// 2MiB - 512B later that the volume has ended.
	byte boot_buf[512], temp_buf[512];
	readsector(lba, 1, buffer_addr);
	memcpy(&boot_buf, (uint64_t*)buffer_addr, sizeof(boot_buf));

	return vol;
}