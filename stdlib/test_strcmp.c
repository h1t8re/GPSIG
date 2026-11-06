#include <stdio.h>
#include "stdlib.h"

int main(int argc, char const *argv[])
{
	char *str0 = "012345\0";
	char *str1 = "6789\0";
	int result0 = strcmp(str0, str0);
	int result1 = strcmp(str0, str1);
	printf("strcmp(\'%s\', \'%s\') = %d\n", str0, str0, result0);
	printf("strcmp(\'%s\', \'%s\') = %d\n", str0, str1, result1);
	return 0;
}