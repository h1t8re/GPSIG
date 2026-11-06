#include <stdio.h>
#include <stdlib.h>
#include "stdlib.h"

int main()
{
	const char *file_name = strdup("./content_to_read.txt");
	const char *content_of_file = read_file_v1(file_name);
	printf("The file %s contains:\n", file_name);
	printf("%s\n", content_of_file);
	return 0;
}