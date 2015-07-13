#include <io.h>

typedef unsigned char bool;
#define false 0
#define true  !false

static int 
__fputhex(int n, bool upper) 
{
	int tmp, p = 0;
    char noZeroes = 1;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (!tmp && noZeroes)
            continue;
        if (tmp >= 0xA) {
            noZeroes = 0;
            upper ? putchar(tmp-0xA+'A') : putchar(tmp-0xA+'a');
        } else {
            noZeroes = 0;
            putchar(tmp+'0');
        }
        p++;
    }
    tmp = n & 0xF;
    if (tmp >= 0xA)
        upper ? putchar(tmp-0xA+'A') : putchar(tmp-0xA+'a');
    else
        putchar(tmp+'0');
    return ++p;
}

/*
static char* itoa(int val, int base){
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];	
}
*/

// This is my own, pretty clean (so I hope) implementation of vfprintf().
// At least, I like it better than Torvalds's.
int 
vprintf(const char *fmt, va_list arg) 
{
	int len = 0;
	bool pct = false;				// Is the next character a percent sign?
	for (; *fmt != '\0'; fmt++, len++) {
		if (pct) {
			switch (*fmt) {
				case '%':
					putchar('%');
					break;
				case 's':
					puts(va_arg(arg, const char*));	
					break;
				case 'c':
					putchar(va_arg(arg, int));
					break;
				case 'u':
				case 'i':
				case 'd':
					{
						int n = va_arg(arg, int);
						if (!n)
							putchar('0');
						else {
							int acc = n;
							char c[32];
							int i = 0;
							while (acc > 0) {
								c[i] = '0' + acc%10;
								acc /= 10;
								i++;
							}
							c[i] = 0;
							len += i-1;
							char c2[32];
							c2[i--] = 0;
							int j = 0;
							while(i >= 0)
								c2[i--] = c[j++];
							puts(c2);
						}
					}
					break;
				case 'x':
					len += __fputhex(va_arg(arg, int), false)-1;
					break;
				case 'X':
					len += __fputhex(va_arg(arg, int), true)-1;
					break;
				case 'p':
					puts("0x");
					len += __fputhex((int64_t)va_arg(arg, void*), false)-1;
					break;
				case 'n':
					{
						int *i = va_arg(arg, int*);
						// For some reason, *i=len+1 adds two to "i".
						*i = len+1;
					}
					break;
				case 'o':
					{
						// Kind of a "meh" implementation of octal.
						// It works, though... unfortunately, it can print only up to 64 characters.
						char result[64];
						int t = va_arg(arg, int), m = 0;
						do {
							t /= 8;
							int rem = t % 10;
							result[m++] = t ? (rem > 9)? (rem-10) + 'a' : rem + '0' : '0';
						} while (t);
						for (; m >= 0; m--)
							putchar(result[m]);
					}
					break;
				default:
					len++;					// Because of the extra "%" character
					putchar('%');
					putchar(*fmt);
			}
			pct = false;
		} else {
			if (*fmt == '%')
				pct = true;
			else
				putchar(*fmt);
		}
	}
	return len;
}

int 
printf(const char *fmt, ...) 
{
	va_list a;
	va_start(a, fmt);
	int y = vprintf(fmt, a);
	va_end(a);
	return y;
}