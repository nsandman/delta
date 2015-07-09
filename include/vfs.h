#ifndef _VFS_
#define _VFS_

// Most of this is based on JamesM's VFS, because that's
// actually a pretty good one. So yeah.
typedef struct vfs_node {
	char name[256];
	uint32_t permissions;
	uint32_t user;
	uint32_t group;
	uint32_t flags;
	uint32_t inode;
	uint32_t size;
	struct vfs_node *ptr;
} vfs_node_t;

struct dirent {
	char name[256];
	u32int inode;
};

typedef u32int (*read_type_t)(struct fs_node*,u32int,u32int,u8int*);
typedef u32int (*write_type_t)(struct fs_node*,u32int,u32int,u8int*);
typedef void (*open_type_t)(struct fs_node*);
typedef void (*close_type_t)(struct fs_node*);
typedef struct dirent * (*readdir_type_t)(struct fs_node*,u32int);
typedef struct fs_node * (*finddir_type_t)(struct fs_node*,char *name);

typedef enum vfs_flags {
	FS_FILE        = 0x01,
	FS_DIRECTORY   = 0x02,
	FS_CHARDEVICE  = 0x03,
	FS_BLOCKDEVICE = 0x04,
	FS_PIPE        = 0x05,
	FS_SYMLINK     = 0x06,
	FS_MOUNTPOINT  = 0x08
}

#endif