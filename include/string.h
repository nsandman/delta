#ifndef _STRING_
#define _STRING_

int strlen(const char *str) {
	int i;
	while(str[++i]);
	return i;
}

#endif