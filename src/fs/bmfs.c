/* Reads a BareMetal filesystem-formatted volume.
   Also probably the simplest filesystem to use as
   a template for any future kernel FSes.       */

#include <hdd.h>
#include <vfs.h>
#include <fs/bmfs.h>
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

// A lot of this code is also based of code
// from the BMFS utility (github.com/returninfinity/bmfs).
