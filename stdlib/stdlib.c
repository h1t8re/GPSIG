/*
	Copyright (c) Chems Eddine h1t8re from 06/02/1996 After Jesus Christe.
*/

#include <stdio.h>
#include <stdlib.h>

/*
 *	strlen is counting the number of characters of the chaine of characters str..
 *	It s return an Integer length..
 */
int strlen(const char *str)
{
        int length = 0;
        while(*(str+(length*sizeof(char))) != '\0')
                length++;
        return length;
}

/*
 * Complexity:
 * length until '\0'
 */


/*
 *	strdup is dynamically duplicating a chaine of character into the memory..
 *	It s returning a chaine of characters
 */
char *strdup(const char *str)
{
        int str_len = 0;
        char *str_dup = (char *)malloc(sizeof(char));
        while( *(str+(str_len*sizeof(char))) != '\0' )
        {
                *(str_dup+(str_len*sizeof(char))) = *(str+(str_len*sizeof(char)));
                str_len++;
                str_dup = (char *)realloc(str_dup, (str_len+1)*sizeof(char));
        }
        *(str_dup+(str_len*sizeof(char))) = '\0';
        return str_dup;
}

/*
 * strcontains is checking if the chaine of charaters str0 is containing
 * another chaine of characters str1..
 * the condition is that
 * strlen(str0) > strlen(str1)
 * It s returning True 0 or False 1
 */
int strcontains(const char *str0, const char *str1)
{
	int i = 0;
        int j = 0;
        int len1 = strlen(str1);

        while((str0[i+j] != '\0') & (str1[j] != '\0'))
        {
                if(str0[i+j] == str1[j])
                {
                        j = j +1;
                }else{
                      	j = 0;
                        i = i +1;
                }

                if(j == len1)
                {
                        return 0;
                }
        }
        return 1;
}

/*
 * The complexity of strcontians
 * if return 0 : at max 4.(i + j)
 * if return 1 : at max 4.(i + j -1)
 *
*/



/*
 * strcmp is comparing two chaines of characters ..
 * their are constant s by traitment of program himself..
 * It s doing ;half check; wich mean that
 * two conditions are removed from the program ..
 * like the end of str1 and the check (i == strlen(str0))

 * It do double check mirroring, work in invert for double and half check..
 * Mirroring is to link both chaines of characters
 */
int strcmp(const char *str0,const char *str1)
{
        int len0 = strlen(str0);
	int len1 = strlen(str1);

	if(len0 != len1)
                return 1;

	int i = 0;
	while((*(str0+(i*sizeof(char))) == (*(str1+(i*sizeof(char))))) & (*(str0+(i*sizeof(char))) != '\0'))
                i++;

	if(i == len1)
		return 0;

	return 1;
}
/*
 * Complexity:
 * Half Check Mirroring
 * strlen(str0) + strlen(str1) +1
 *             +
 * 3**i until '\0' of str0
 *     1 + strlen(str1)
 * ===> return 0
 */



/*
 * strconcatenate is concatenating two chaines of charcaters
 * to give birth of one chaine of characters
 * It s returning one chaine of characters
 */
const char *strconcatenate(const char *str0, const char *str1)
{
	int i = 0;
	char *result = (char *)malloc(sizeof(char));
	while(i < strlen(str0))
	{
		*(result+(i*sizeof(char))) = *(str0+(i*sizeof(char)));
		i++;
		result = (char *)realloc(result, (i+1)*sizeof(char));
	}
	while(i < strlen(str0)+strlen(str1))
	{
		*(result+(i*sizeof(char))) = *(str1+((i-strlen(str0))*sizeof(char)));
		i++;
		result = (char *)realloc(result, (i+1)*sizeof(char));
	}
	result[i] = '\0';
	return result;
}

/*
 * read_input is reading from the buffer character by character
 * until heating new line
 */
const char *read_input()
{
        char *buffer = (char *)malloc(sizeof(char));
        int buffer_len = 0;
        while((buffer[buffer_len] = getchar()) != '\n')
        {
                buffer_len++;
                buffer = (char *)realloc(buffer, (buffer_len+1)*sizeof(char));
        }
        buffer[buffer_len] = '\0';
        return buffer;
}

/*
 * read_file is reading dynamically with fread from the file1 after opening it ..
 * It s returning a chaine of characters ..
 */
char *read_file(const char *restrict file_name)
{
        const char *restrict mode = strdup("r\0");
        FILE *restrict fd = fopen(file_name, mode);
        if(fd == NULL)
                return NULL;
        char *buffer = (char *)malloc(sizeof(char));
        int buffer_len = 0;
        do
        {
                buffer_len = buffer_len +1;
                fread(buffer+((buffer_len-1)*sizeof(char)), sizeof(char), 1, fd);
                buffer = (char *)realloc(buffer, (buffer_len+1)*sizeof(char));
        }while(*(buffer+((buffer_len-1)*sizeof(char))) != EOF);
        *(buffer+((buffer_len-1)*sizeof(char))) = '\0';
        return buffer;
}

/*
 * read_file_v1 is reading from the file with fgetc after opening it ..
 * It s returning a chaine of characters
*/
const char *read_file_v1(const char *file_name)
{
        const char *restrict mode = strdup("r\0");
        FILE *restrict fd = fopen(file_name, mode);
        if(fd == NULL)
                return NULL;
        char *buffer = (char *)malloc(sizeof(char));
        int buffer_len = 0;
        while((buffer[buffer_len] = fgetc(fd)) != EOF)
        {
                buffer_len++;
                buffer = (char *)realloc(buffer, (buffer_len+1)*sizeof(char));
        }
        buffer[buffer_len] = '\0';
        return buffer;
}

const int shift_mask_left(const int mask, const int i)
{
        const int mask_shifted = mask << i;
        return mask_shifted;
}

const int and_operation(const int number, const int mask_shifted)
{
	const int result = number & mask_shifted;
        return result;
}

const int shift_result_right(const int number, const int i)
{
        const int result = number >> i;
        return result;
}

void convert_integer_to_binary(int *restrict array, const int number, const int mask, const int architecture)
{
        int i = 0;
        while(i < architecture)
        {
                const int mask_shifted = shift_mask_left(mask, i);
                const int and_result = and_operation(number, mask_shifted);
                array[i] = shift_result_right(and_result, i);
                i = i +1;
        }
}

double pow(double x, double y)
{
        if(y == 1)
                return x;
        return pow(x*x, y-1);
}

int convert_binary_to_integer(int *array, int architecture)
{
        int number = 0;
        int i = architecture-1;
        while(i >= 0)
        {
                if(array[i] == 1)
                        number = number + pow(2, i+1);
                i = i -1;
        }
        return number;
}

/*
 * find_string_position is looking after the string ..
 * in the number of the occurence position ..
 * from buffer
 */
int find_string_position(const char *buffer, const char *string, const int position)
{
        int i = 0;
        int j = 0;
        int position_found = 0;
        char *temporary_mem;
        while(buffer[i+j] != '\0')
        {
		temporary_mem = (char *)malloc(strlen(string)*sizeof(char));
                while(j < strlen(string))
                {
                        temporary_mem[j] = buffer[i+j];
                        j = j +1;
                }
                temporary_mem[j] = '\0';
                if(strcmp(string, temporary_mem) == 0)
                {
                        position_found = position_found +1;
                        if(position_found == position)
                                return i;
                        i = i +j;
                }else{
                        i = i +1;
                }
                j = 0;
		free(temporary_mem);
        }
        return 0;
}

/*
 * strsplit_v1 is spliting string by spliter..
 * It look after the j eme occurence of spliter in string, it s k ..
 * by a whileloop is dynamically getting all characters from string to buffer
 * until heating k..
 * After that it s closing buffer and duplicating it into array[a]..
 * Looking another time after the j eme occurence of spliter in string, it's k
 * going to the next iteration of the big whileloop until heating 0 of string
 * It s returning a table of chaines of characters
 */
char **strsplit_v1(const char *string,const char *spliter)
{
        char **array = (char **)malloc(sizeof(char *));
        char *buffer;
        int i = 0;
        int j = 1;
        int k = find_string_position(string, spliter, j);
        int a = 0;
        int c = 0;
        while(string[i] != '\0')
        {
                buffer = (char *)malloc(sizeof(char));
                while(((i < k) & (string[i] != '\0')))
                {
                        buffer[c] = string[i];
                        c = c +1;
                        i = i +1;
                        buffer = (char *)realloc(buffer, (c+1)*sizeof(char));
                }
                buffer[c] = '\0';
                array[a] = strdup(buffer);
                i = i + strlen(spliter);
                j = j +1;
                k = find_string_position(string, spliter, j);
                if(k == 0)
                        k = strlen(string);
                c = 0;
                a = a +1;
                array = (char **)realloc(array, (a+1)*sizeof(char *));
                free(buffer);
        }
        array[a] = '\0';
        return array;
}

/* Sum of Complexity of find_string_position at j occurence
 * + at each occurence the complexity of strdup(buffer)
 * + complexity of the before last occurence of spliter in string
 * until the last occurence of spliter in string
 *
 */



/*
 * get_data_by_key is spliting data by separator..
 * iterating over each splited_data ..
 * filling temporary memory array by data from each splited_data
 * After removing spaces at
 * the begining of the splited_data chaine of characters
 * comparing temporary memory with key.. If it s True ..
 * duplicate the array splited_data into array[k]..
 * It s returning an array of chaines of characters
 */
char **get_data_by_key(char *data, char *key, char *separator)
{
	int i = 0;
	int j = 0;
	int c = 0;
	int k = 0;
	char *temporary_mem = (char *)malloc(strlen(key));
	char **array = (char **)malloc(sizeof(char *));
	char **splited_data = strsplit_v1(strdup(data), strdup(separator));
	while(splited_data[i] != '\0')
	{
		while(j < strlen(key))
                {
			if(splited_data[i][c+j] == ' ')
			{
				c = c +1;
				continue;
			}else
			{
				temporary_mem[j] = splited_data[i][c+j];
                        	j = j +1;
			}
                }
                temporary_mem[j] = '\0';
		if(strcmp(key, temporary_mem) == 0)
		{
			array[k] = strdup(splited_data[i]);
			k = k +1;
			array = (char **)realloc(array, (k+1)*sizeof(char *));
		}
		i = i +1;
		j = 0;
		c = 0;
	}
	array[k] = '\0';
	return array;
}