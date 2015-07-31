#ifndef _STRING_
#define _STRING_

#include <stddef.h>

size_t strlen(const char *str); // string.asm
char  *strcat(char*, const char*);
char  *strcpy(char*, const char*);
int    strncmp(const char*, const char*, size_t);
char  *strchr(const char*, int);

void *memcpy(void*, const void*, size_t);
void *memmove(void*, const void*, unsigned);
void *memset(void*, register int, register size_t);

int tolower(int);
int isupper(int);

#endif