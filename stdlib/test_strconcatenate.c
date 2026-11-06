#include <stdio.h>
#include "stdlib.h"

int main()
{
	const char *str0 = strdup("01234\0");
	const char *str1 = strdup("5678\0");
	printf("strconcatenate(%s, %s) = %s\n", str0, str1, strconcatenate(str0, str1));
	return 0;
}