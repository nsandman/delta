int strlen(const char *str) {
	int i;
	while (str[++i]);
	return i;
}