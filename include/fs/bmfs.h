#ifndef _BMFS_
#define _BMFS_

// All of this information is from:
// github.com/ReturnInfinity/BMFS/wiki/BareMetal-File-System
typedef struct bv {
	uint64_t start;
	uint64_t end;
	uint16_t nfiles;
	char    *files[];
} bmfs_volume_t;

/*
 * Filename (32 bytes) - Null-terminated ASCII string Starting Block number (64-bit unsigned int)
 * Blocks reserved (64-bit unsigned int)
 * File size (64-bit unsigned int)
 * Unused (8 BYTES)
 */
typedef struct file {
	char name[32];
	uint64_t starting;
	uint64_t reserved;
	uint64_t size;
	uint64_t unused;
} bmfs_file_t;

bmfs_volume_t *bmfs_getvolume(int, uint64_t);	// Get a BMFS volume "object"

#endif