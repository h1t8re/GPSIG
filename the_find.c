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
	MAp->coordinate[0] = -1;
	MAp->coordinate[1] = -1;
	MAp->right = NULL;
	MAp->down = NULL;
	MAp->left = NULL;
	MAp->up = NULL;
	return MAp;
}

void print(map *Map)
{
	//if((Map != NULL) & (Map->coordinate[0] != -1) & (Map->coordinate[1] != -1))
	printf("(%d, %d)\n", Map->coordinate[0], Map->coordinate[1]);
	if(Map->right != NULL)
		print(Map->right);
	else if(Map->down != NULL)
		print(Map->down);
	//if(Map->left != NULL)
	//	print(Map->left);
	//else if(Map->up != NULL)
	//	print(Map->up);
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
	while(array0[i] != '\0')
	{
		array1 = strsplit_v1(strdup(array0[i]), strdup(spliter1));
		coord  = get_xy(array1[0]);
		MAp[k] = initialize_map(); 
		MAp[k]->coordinate[0] = coord[0];
		MAp[k]->coordinate[1] = coord[1];
		array2 = strsplit_v1(strdup(array1[1]), strdup(spliter2));
		printf("(%d, %d):\n", coord[0], coord[1]);
		while(array2[j] != '\0')
		{
			if(strlen(array2[j]) != 0)
			{
				coord = get_xy(array2[j]);
				MAp[k] = construct_the_map(MAp[k], coord, 0, 0);
				printf("coord = (%d, %d)\n", coord[0], coord[1]);
			}
			j++;
		}
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

map *linking_the_map(map *Map, map *MAp)
{
	if(Map != NULL)
	{
	if((Map->coordinate[0] == MAp->coordinate[0]) & (Map->coordinate[1] == MAp->coordinate[1]))
	{
		Map = MAp;
		print(MAp);
		printf("(%d, %d)\n", Map->coordinate[0], Map->coordinate[1]);
		return Map;	
	}
	if(Map->right != NULL)
	{
		Map->right->left = Map;
		Map = Map->right;
		linking_the_map(Map, MAp);
		printf("right = (%d, %d)\n", Map->coordinate[0], Map->coordinate[1]);
		Map = Map->left;
		return Map;	
	}else if(Map->down != NULL)
	{
		Map->down->up = Map;
		Map = Map->down;
		printf("down = (%d, %d)\n", Map->coordinate[0], Map->coordinate[1]);
		linking_the_map(Map, MAp);
		Map = Map->up; 
		return Map;
	}
	}
}


int main()
{
	const char *data = read_file_v1("./space.glyph");
	int k = 0;
	printf("%s\n", data);
	map *Map = initialize_map();
	map **MAp = parse_data_and_construct_the_map(data);
	Map->coordinate[0] = MAp[k]->coordinate[0];
	Map->coordinate[1] = MAp[k]->coordinate[1];
	while(MAp[k] != NULL)
	{
		Map = linking_the_map(Map, MAp[k]);
		printf("MAp[k]->coordinate[0] = %d | MAp[k]->coordinate[1] = %d\n", MAp[k]->coordinate[0], MAp[k]->coordinate[1]);
		k++;
		//printf("Printing coordinate of the map .. \n");
		//print_coordinate_of_the_map(Map);
	}
	//print_the_map(Map);
	return 0;
}
