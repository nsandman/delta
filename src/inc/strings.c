#include <stringf.h>

char*
strcat(char *dest, const char *src) 
{
	char *rdest = dest;
	while (*dest)
		dest++;
	while ((*dest++ = *src++));
	return rdest;
}

size_t 
strlen(const char *str) 
{
	size_t i = 0;
	while (str[++i]);
	return i;
}

void* 
memcpy(void* s1, const void* s2, size_t n) 
{
  void* b = s1;
  while (n--)
  {
    *(char*)s1 = *(const char*)s2;
    s1 = (void*)((char*)s1+1);
    s2 = (const void*)((const char*)s2+1);
  }
  return b;
}

void*
memmove(void *destaddr, const void *sourceaddr, unsigned length) 
{
  char *dest = destaddr;
  const char *source = sourceaddr;
  if (source < dest)
    /* Moving from low mem to hi mem; start at end.  */
    for (source += length, dest += length; length; --length)
      *--dest = *--source;
  else if (source != dest)
    /* Moving from hi mem to low mem; start at beginning.  */
    for (; length; --length)
      *dest++ = *source++;

  return destaddr;
}

void*
memset(void *dst, register int c, register size_t n) 
{
	if (n != 0) {
		register char *d = dst;
		do {
			*d++ = c;
		} while (--n != 0);
	}
	return dst;
}