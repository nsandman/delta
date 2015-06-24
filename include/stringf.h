#ifndef _STRING_
#define _STRING_

#include <stddef.h>

size_t strlen(const char *str); // string.asm
char *strcat(char*, const char*);

void* memcpy(void*, const void*, size_t);
void *memmove(void*, const void*, unsigned);
void *memset(void*, register int, register size_t);

#endif