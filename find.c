#include <stdio.h>
#include <stdlib.h>
#include "include/stdlib.h"

typedef struct Map{
	int *coordinate;
	struct Map *down;
	struct Map *up;
	struct Map *right;
	struct Map *left;
}map;

int *get_xy(char *coordinate)
{
	int i = 0;
	int b = 0;
	char *x = (char *)malloc(sizeof(char));
	char *y = (char *)malloc(sizeof(char));
	int *coord = (int *)malloc(2*sizeof(int));
	while(coordinate[i+1] != ',')
	{
		x[i] = coordinate[i+1];
		i++;
		x = (char *)realloc(x, (i+1)*sizeof(char));
	}
	x[i] = '\0';
	i = i +3;
	b = i;
	while(coordinate[b] != ')')
	{
		y[b-i] = coordinate[b];
		b++;
		y = (char *)realloc(y, (b+1)*sizeof(char));
	}
	y[b-i] = '\0';
	coord[0] = atoi(x);
	coord[1] = atoi(y);
	return coord;
}

map *initialize_map()
{
	map *MAp = (map *)malloc(sizeof(struct Map *));
	MAp->coordinate = (int *)malloc(2*sizeof(int));
	MAp->coordinate[0] = -3;
	MAp->coordinate[1] = -3;
	MAp->right = NULL;
	MAp->down = NULL;
	MAp->left = NULL;
	MAp->up = NULL;
	return MAp;
}

void print_coordinate_of_the_map(map *MAp)
{
	if((MAp->coordinate[0] != -1) & (MAp->coordinate[1] != -1))
		printf("MAp->coordinate[0] = %d | MAp->coordinate[1] = %d\n", MAp->coordinate[0], MAp->coordinate[1]);
	if(MAp->right != NULL)
		print_coordinate_of_the_map(MAp->right);
	if(MAp->down != NULL)
		print_coordinate_of_the_map(MAp->down);
	if(MAp->up != NULL)
		print_coordinate_of_the_map(MAp->up);
	if(MAp->left != NULL)
		print_coordinate_of_the_map(MAp->left);

}

map *construct_the_map(map *MAp, int *coordinate, int x, int y)
{
	printf("x = %d | y = %d\n", x, y);
	if(coordinate[0] == x)
	{
		MAp->right = initialize_map();
		MAp->right->coordinate[0] = coordinate[0];
		MAp->right->coordinate[1] = coordinate[1];
		MAp->right->left = MAp;
	}
	else if(coordinate[1] == y)
        {
                MAp->down = initialize_map();
                MAp->down->coordinate[0] = coordinate[0];
                MAp->down->coordinate[1] = coordinate[1];
        	MAp->down->up = MAp;
	}
	if(coordinate[0] > x)
	{
		MAp->right = initialize_map();
		MAp->right->left = MAp;
		construct_the_map(MAp->right, coordinate, x+1, y);
	}
	else if(coordinate[1] > y)
        {               
                MAp->down = initialize_map();
		MAp->down->up = MAp;
                construct_the_map(MAp->down, coordinate, x, y+1);
	}

	return MAp;
}

map **parse_data_and_construct_the_map(const char *data)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int *coord;
	map **MAp = (map **)malloc(sizeof(struct Map **));
	char *spliter0 = strdup("\n\0");
	char *spliter1 = strdup(":\0");
	char *spliter2 = strdup("  \0");
	char **array0 = strsplit_v1(strdup(data), strdup(spliter0));
	char **array1;
	char **array2;
	int x = 0;
	int y = 0;
	while(array0[i] != '\0')
	{
		array1 = strsplit_v1(strdup(array0[i]), strdup(spliter1));
		coord  = get_xy(array1[0]);
		MAp[k] = initialize_map(); 
		MAp[k]->coordinate[0] = coord[0];
		MAp[k]->coordinate[1] = coord[1];
		printf("(%d, %d):  ", MAp[k]->coordinate[0], MAp[k]->coordinate[1]);
		array2 = strsplit_v1(strdup(array1[1]), strdup(spliter2));
		while(array2[j] != '\0')
		{
			if(strlen(array2[j]) != 0)
			{
				coord = get_xy(array2[j]);
				MAp[k] = construct_the_map(MAp[k], coord, 0, 0);
				printf("coord = (%d, %d)  ", coord[0], coord[1]);
			}
			j++;
		}
		printf("\n");
		j = 0;
		k++;
		MAp = (map **)realloc(MAp, (k+1)*sizeof(struct Map **));
		MAp[k] = NULL;
		i++;
		free(array1);
		free(array2);
		free(coord);
	}
	MAp[k] = NULL;
	return MAp;
}

void print_the_map(map **MAp)
{
	int i = 0;
	int k = 0;
	while(MAp[k] != NULL)
	{
		printf("k = %d", k);
		if(MAp[k]->right != NULL)
		{
			for(int j = 0; j < (MAp[k]->right->coordinate[0] - MAp[k]->coordinate[0]); j++)
			{	
				printf("-");
			}
		}
		i = 0;
		while(i <= MAp[k]->right->coordinate[0])
		{
			printf(" ");
			i++;
		}
		i = 0;
		printf("|");
		k++;
	}
}

int main()
{
	const char *data = read_file_v1("./space.glyph");
	printf("%s\n", data);
	map **MAp = parse_data_and_construct_the_map(data);
	//print_the_map(MAp);
	return 0;
}
