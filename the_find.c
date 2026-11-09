#include <stdio.h>
#include <stdlib.h>
#include "include/stdlib.h"

typedef struct Map{
	int *coordinate;
	struct Map *down;
	struct Map *up;
	struct Map *right;
	struct Map *left;
}MAP;

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

MAP *allocate_memory_and_initialize_noeud()
{
	MAP *map = (MAP *)malloc(sizeof(struct Map));
	map->coordinate = (int *)malloc(2*sizeof(int));
	map->coordinate[0] = -1;
	map->coordinate[1] = -1;
	map->right = NULL;
	map->down = NULL;
	map->left = NULL;
	map->up = NULL;
	return map;
}

void printing_the_map(MAP *map)
{
	if((map->coordinate[0] != -1) & map->coordinate[1] != -1)
		printf("map = (%d, %d)\n", map->coordinate[0], map->coordinate[1]);
	if(map->right != NULL)
	{
		//printf("map = (%d, %d)\n", map->coordinate[0], map->coordinate[1]);
		printing_the_map(map->right);
	}
	if(map->down != NULL)
	{
		//printf("map = (%d, %d)\n", map->coordinate[0], map->coordinate[1]);
	
		printing_the_map(map->down);
	}
	//if(map->left != NULL)
	//	print(map->left);
	//if(map->up != NULL)
	//	print(map->up);
}

MAP *construct_the_branch(MAP *branch, int *coordinate, int x, int y)
{
	printf("x = %d | y = %d\n", x, y);
	if(branch == NULL)
		branch = allocate_memory_and_initialize_noeud();
	if((coordinate[0] == x) & (coordinate[1] == y))
	{
		branch->coordinate[0] = coordinate[0];
		branch->coordinate[1] = coordinate[1];
		//printf("branch = (%d, %d)\n", branch->coordinate[0], branch->coordinate[1]);
		return branch;
	}
	if(coordinate[0] > x)
	{
		if(branch->right == NULL)
		{
			branch->right = allocate_memory_and_initialize_noeud();
			branch->right->coordinate[0] = x;
			branch->right->coordinate[1] = y;
			branch->right->left = branch;
			branch->right = construct_the_branch(branch->right, coordinate, x+1, y);
		}else
		{
			branch = branch->right;
			branch = construct_the_branch(branch,  coordinate, x+1, y);
			branch = branch->left;
		}
		//printf("branch->right = (%d, %d)\n", branch->coordinate[0], branch->coordinate[1]);
		//return branch;
	}else if(coordinate[1] > y)
        {               
                if(branch->down == NULL)
		{
			branch->down = allocate_memory_and_initialize_noeud();
			branch->down->coordinate[0] = x;
			branch->down->coordinate[1] = y;
			branch->down->up = branch;
                	branch->down = construct_the_branch(branch->down, coordinate, x, y+1);
		}else
		{
			branch = branch->down;
			branch = construct_the_branch(branch,  coordinate, x, y+1);
			branch = branch->up;
		}
		//printf("branch->down = (%d, %d)\n", branch->coordinate[0], branch->coordinate[1]);
		//return branch;
	}
	return  branch;
}

MAP **parse_data_and_construct_branches(const char *data)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int *coord;
	MAP **branches = (MAP **)malloc(sizeof(struct Map *));
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
		branches[k] = allocate_memory_and_initialize_noeud(); 
		branches[k]->coordinate[0] = coord[0];
		branches[k]->coordinate[1] = coord[1];
		array2 = strsplit_v1(strdup(array1[1]), strdup(spliter2));
		printf("(%d, %d):\n", coord[0], coord[1]);
		while(array2[j] != '\0')
		{
			if(strlen(array2[j]) != 0)
			{
				coord = get_xy(array2[j]);
				branches[k] = construct_the_branch(branches[k], coord, 0, 0);
				//printf("branches[%d]\n", k);
				printf("coord = (%d, %d)\n", coord[0], coord[1]);
				//printing_the_map(branches[k]);
			}
			j++;
		}
		j = 0;
		//printing_the_map(branches[k]);
		k++;
		branches = (MAP **)realloc(branches, (k+1)*sizeof(struct Map *));
		branches[k] = NULL;
		i++;
		free(array1);
		free(array2);
		free(coord);
	}
	branches[k] = NULL;
	return branches;
}

MAP *constructing_the_map(MAP *map, MAP *branch)
{
		if((map->coordinate[0] == branch->coordinate[0]) && (map->coordinate[1] == branch->coordinate[1]))
                {
                        map = branch;
                        printf("map = branch = (%d, %d)\n", map->coordinate[0], map->coordinate[1]);        
                	return map;
		}
		if(map->right != NULL)
		{
			map->right = constructing_the_map(map->right, branch);
			return map;
			//printf("right = (%d, %d)\n", map->coordinate[0], map->coordinate[1]);
		}
		if(map->down != NULL)
		{
			map->down = constructing_the_map(map->down, branch);
			return map;
			//printf("down = (%d, %d)\n", map->coordinate[0], map->coordinate[1]);
		}
		return NULL;
}

int main()
{
	const char *data = read_file_v1("./space.glyph");
	int k = 0;
	printf("%s\n", data);
	MAP **branches = parse_data_and_construct_branches(data);
	MAP *map = branches[k];
	printf("%d\n", k);	
	printing_the_map(map);
	k++;
	while(branches[k] != NULL)
	{
		printf("%d\n", k);	
		constructing_the_map(map, branches[k]);
		printing_the_map(map);
		//printf("branches[%d]->coordinate[0] = %d | branches[%d]->coordinate[1] = %d\n", k, branches[k]->coordinate[0], k, branches[k]->coordinate[1]);
		k++;
		//printf("Printing coordinate of the map .. \n");
		//print_coordinate_of_the_map(Map);
	}
	//printing_the_map(map);
	return 0;
}
