#include <stdio.h>
#include <stdlib.h>
#include "stdlib.h"

int main()
{
	const char *str0 = strdup("0123456789\0");
	const char *str1 = strdup("7\0");
	const char *str2 = strdup("=\0");
	printf("strcontains(%s, %s) = %d\n", str0, str1, strcontains(str0, str1));
	printf("strcontains(%s, %s) = %d\n", str0, str2, strcontains(str0, str2));
	return 0;
}