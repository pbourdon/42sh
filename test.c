#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"


int main(void)
{
	char *str;
	char **ptr;

	str = malloc(sizeof(char) * 256);
	str = "abc def";
	ptr = &str;
	int c = **ptr;
	write(1, &c, 1);
	c = **ptr + 10;
	write(1, &c, 1);
}
