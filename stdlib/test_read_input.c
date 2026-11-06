#include <stdio.h>
#include "stdlib.h"

int main()
{
	printf("Type something \n");
	const char *buffer = read_input();
	printf("The content read is %s\n", buffer);
	return 0;
}