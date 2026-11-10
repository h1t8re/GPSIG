/*
	Copyright (c) Chems Eddine h1t8re (borguate) from 06021996 After Jesus Christe.
*/
#include <stdio.h>
#include <stdlib.h>
#include "include/stdlib.h"

typedef struct Map{
	int *coordinate;
	struct Map *down;
	struct Map *up;
	struct Map *right;
	struct Map *left;
}TREE;

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

TREE *allocate_memory_and_initialize_noeud()
{
	TREE *tree = (TREE *)malloc(sizeof(struct Map));
	tree->coordinate = (int *)malloc(2*sizeof(int));
	tree->coordinate[0] = -1;
	tree->coordinate[1] = -1;
	tree->right = NULL;
	tree->down = NULL;
	tree->left = NULL;
	tree->up = NULL;
	return tree;
}

void printing_the_tree(TREE *tree)
{
	printf("tree = (%d, %d)\n", tree->coordinate[0], tree->coordinate[1]);
	if(tree->right != NULL)
	{
		printing_the_tree(tree->right);
	}
	if(tree->down != NULL)
	{
		printing_the_tree(tree->down);
	}
}

TREE *construct_the_branch(TREE *branch, int *coordinate, int x, int y)
{
	if(branch == NULL)
		branch = allocate_memory_and_initialize_noeud();
	if((coordinate[0] == x) & (coordinate[1] == y))
	{
		branch->coordinate[0] = coordinate[0];
		branch->coordinate[1] = coordinate[1];
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
			branch->right->left = branch;
			branch = branch->right;
			branch = construct_the_branch(branch,  coordinate, x+1, y);
			branch = branch->left;
		}
	}
	else if(coordinate[1] > y)
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
			branch->down->up = branch;
			branch = branch->down;
			branch = construct_the_branch(branch,  coordinate, x, y+1);
			branch = branch->up;
		}
	}
	return  branch;
}

TREE **parse_data_and_construct_branches(const char *data)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int *coord;
	TREE **branches = (TREE **)malloc(sizeof(struct Map *));
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
		while(array2[j] != '\0')
		{
			if(strlen(array2[j]) != 0)
			{
				coord = get_xy(array2[j]);
				branches[k] = construct_the_branch(branches[k], coord, branches[k]->coordinate[0], branches[k]->coordinate[1]);
			}
			j++;
		}
		j = 0;
		k++;
		branches = (TREE **)realloc(branches, (k+1)*sizeof(struct Map *));
		branches[k] = NULL;
		i++;
		free(array1);
		free(array2);
		free(coord);
	}
	branches[k] = NULL;
	return branches;
}

TREE *duplicating_the_branch(TREE *tree, TREE * branch)
{
	tree->coordinate[0] = branch->coordinate[0];
	tree->coordinate[1] = branch->coordinate[1];
	if(branch->right != NULL)
	{
		tree->right = branch->right;
		tree->right = duplicating_the_branch(tree->right, branch->right);
	}
	if(branch->down != NULL)
	{
		tree->down = branch->down;
		tree->down = duplicating_the_branch(tree->down, branch->down);
	}
	return tree;

}

TREE *constructing_the_tree(TREE *tree, TREE *branch)
{
		if((tree->coordinate[0] == branch->coordinate[0]) && (tree->coordinate[1] == branch->coordinate[1]))
                {
			tree = duplicating_the_branch(tree, branch);
		}
		if(tree->right != NULL)
		{
			constructing_the_tree(tree->right, branch);
		}
		if(tree->down != NULL)
		{
			constructing_the_tree(tree->down, branch);
		}
		return tree;
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./find [coordinate_file_name]\n");
		return 1;
	}
	const char *data = read_file_v1(strdup(argv[1]));
	int k = 0;
	printf("%s\n", data);
	TREE **branches = parse_data_and_construct_branches(data);
	TREE *tree = branches[k];
	k++;
	while(branches[k] != NULL)
	{
		tree = constructing_the_tree(tree, branches[k]);
		k++;
	}
	printing_the_tree(tree);
	return 0;
}
