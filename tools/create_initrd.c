/*
 * Copyright (c) 2015, Noah Sandman
 * All rights reserved.

 * Redistribution and use in source and binary forms, with 
 * or without modification, are permitted provided that the
 * following conditions are met:

 * 1. Redistributions of source code must retain the 
 *    above copyright notice, this list of conditions and 
 *    the following disclaimer.

 * 2. Redistributions in binary form must reproduce the 
 *    above copyright notice, this list of conditions and 
 *    the following disclaimer in the documentation and/or 
 *    other materials provided with the distribution.

 * 3. Neither the name of the copyright holder nor the names 
 *    of its contributors may be used to endorse or promote 
 *    products derived from this software without specific prior 
 *    written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY 
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.

               *--------------------------*              

 * This tool will create an initial ramdisk for the Delta operating system.
 * The ramdisk uses a very simple flat filesystem, meant to preserve space. It
 * is a flat system. First, it starts with a global header:

 * uint32_t nfiles

 * nfiles is the number of files in the image.

 * Then it is followed by "nfile" file headers:

 * char name[16]
 * uint32_t size

 * Then, the file data follows immediately. Then, the next header. If not, the
 * image is over.
 * Truthfully, the format is more like an archive than an image, so think of it
 * more like that.

 * The last eight bytes are this sequence:
 * CC 00 00 CC FF 00 00 FF

 * So. Let's get started!
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// To avoid awful use of the shift key
typedef FILE* stream;

struct file_header {
	const char *name;
	uint32_t    size;	
};

uint8_t
write_file(stream initrd, const char *name, const char *path, const char *fc)
{
	stream file = fopen(path, "rb");
	if (!file) {
		fprintf(stderr, "%s: \033[1;31mfatal error:\033[0m Could not open file \"%s\"\n", fc, path);
		return 1;
	}
	fseek(file, 0L, SEEK_END);
	int sz = ftell(file);
	rewind(file);
	printf("\033[1m%s\033[0m being written to \033[1m%s\033[0m (size: %d)\n", path, name, sz);
	for (int i = 0; i < 15; i++)
		fputc(name[i]?name[i]:0,initrd);
	fwrite(&sz, sizeof(sz), 1, initrd);
	char c;
	while ((c = getc(file)) != EOF)
        fputc(c, initrd);
	return 0;
}

int
main(int argc, const char **argv)
{
	if (argc < 3)
		printf("USAGE: %s [outfile] [file1] [file2] etc...\n", *argv);
	else {
		stream initrd = fopen(*(++argv), "wb");
		uint32_t f = argc-2;
		fwrite(&f, 4, 1, initrd);
		for (uint8_t i = 2; i < argc; i++) {
			const char *c = strrchr(*(++argv), '/');
			write_file(initrd, c?c+1:*argv, *argv, *(argv-i));
		}
		uint64_t z = 0xcc0000ccff0000ff;
		fwrite(&z, sizeof(z), 1, initrd);
		fclose(initrd);
	}
	return 0;
}