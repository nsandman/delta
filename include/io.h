#ifndef __NSTDIO_H
#define __NSTDIO_H

#include <stdarg.h>

int vprintf(const char *fmt, va_list arg);
int printf(const char *fmt, ...);

#endif