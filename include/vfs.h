#ifndef _VFS_
#define _VFS_

#include <stdint.h>

struct fs_node;

// Most of this is based on JamesM's VFS, because that's
// actually a pretty good one. So yeah.
typedef uint32_t (*read_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);
typedef uint32_t (*write_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);
typedef void (*open_type_t)(struct fs_node*);
typedef void (*close_type_t)(struct fs_node*);
typedef struct dirent * (*readdir_type_t)(struct fs_node*,uint32_t);
typedef struct fs_node * (*finddir_type_t)(struct fs_node*,char *name);

typedef struct fs_node {
	char name[256];
	uint32_t permissions;
	uint32_t user;
	uint32_t group;
	uint32_t flags;
	uint32_t inode;
	uint32_t size;
	read_type_t read;
	write_type_t write;
	open_type_t open;
	close_type_t close;
	readdir_type_t readdir;
	finddir_type_t finddir;
	struct vfs_node *ptr;
} vfs_node_t;

extern fs_node_t *fs_root;

struct dirent {
	char name[256];
	uint32_t inode;
};

enum vfs_flags {
	FS_FILE        = 0x01,
	FS_DIRECTORY   = 0x02,
	FS_CHARDEVICE  = 0x03,
	FS_BLOCKDEVICE = 0x04,
	FS_PIPE        = 0x05,
	FS_SYMLINK     = 0x06,
	FS_MOUNTPOINT  = 0x08
};

#endif
