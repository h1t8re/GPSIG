#include <stdio.h>
#include "stdlib.h"

int main(int argc, char *argv[])
{
	char *str = "123456789\0";
	size_t len_of_str = strlen(str);
	printf("%d is length of \'%s\'\n", len_of_str, str);
	char *str1 = "Chems Eddine Lahbabi\0";
	size_t len_of_str1 = strlen(str1);
	printf("%d is length of \'%s\'\n", len_of_str1, str1);
	return 0;
}