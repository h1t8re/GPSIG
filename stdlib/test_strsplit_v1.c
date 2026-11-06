#include <stdio.h>
#include "stdlib.h"

int main(int argc, char *argv[])
{
	const char *str = "1.22.333.4444.55555.666666.7777777.88888888.999999999\0";
	const char *spliter = ".\0";
	printf("strsplit_v1(\"%s\", \"%s\") is\n", str, spliter);
	char **result = strsplit_v1(str, spliter);
	int i = 0;
	while(result[i] != '\0')
	{
		printf("the array %d contains \'%s\'\n", i, result[i]);
		i++;
	}
	return 0;
}