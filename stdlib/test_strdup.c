#include <stdio.h>
#include "stdlib.h"

int main(int argc, char *argv[])
{
	char *str = "123456789\0";
	char *str_dup = strdup(str);
	printf("duplication of \'%s\' at address %p \nit\'s \'%s\' at address %p\n", str, str, str_dup, str_dup);
	char *str0 = "string_duplication\0";
	char *str_dup0 = strdup(str0);
	printf("duplication of \'%s\' at address %p \nit\'s \'%s\' at address %p\n", str0, str0, str_dup0, str_dup0);

	return 0 ;
}