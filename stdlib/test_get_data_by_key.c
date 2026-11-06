#include <stdio.h>
#include "stdlib.h"
#include <stdlib.h>

int main()
{
	char *data = read_file_v1("./data.txt\0");
	char *key = strdup("2:\0");
	char *separator = strdup("\n\0");
	char **array = get_data_by_key(data, key, separator);
	int i = 0;
	printf("Get data by this key; \"%s\" from \n\"\n%s\"\nis \n", key, data);
	while(array[i] != '\0')
	{
		printf("%s\n", array[i]);
		i = i +1;
	}
	return 0;
}