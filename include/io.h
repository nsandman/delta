#ifndef __NSTDIO_H
#define __NSTDIO_H

#include <stdarg.h>
#include <screen.h>

int vprintf(const char *fmt, va_list arg);
int printf(const char *fmt, ...);
int sprintf(char *str, const char *fmt, ...);

extern int vsprintf(char*, const char*, va_list);

#endif