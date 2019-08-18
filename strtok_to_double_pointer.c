#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * _free - free a double char pointer
 * @list: the double char pointer
 * @count: the number of single char pointers to free
 */
void _free(char **list, int count)
{
	for (; count >= 0; count--)
		do_mem(0, list[count]);
	do_mem(0, list);
}

/**
 * _strtok - split a string into a double char pointer
 * @str: the string to split
 * @delim: any characters to split the string by
 * Return: the double char pointer
 */
char **_strtok(char *str, char *delim)
{
	int i = 0, j = 0, len = 0, count = 0, check = 0;
	char **list;

	for (i = 0, count = 0; str[i]; i++)
	{
		if ((str[i] == delim[0]) && check)
		{
			count++;
			check = 0;
		}
		else if (str[i] != delim[0])
			check = 1;
	}
	if (str)
		count++;
	list = (char **)do_mem((count + 1) * sizeof(char *), NULL);
	if (!list)
		return (NULL);
	for (i = 0, len = 0, count = 0; str[i] || len; i++)
	{
		if (((str[i] == delim[0]) || ((!str[i]) && len)))
		{
			list[count] = (char *)do_mem(sizeof(char) * (len + 1), NULL);
			if (!list[count])
			{
				_free(list, count);
				return (NULL);
			}
			for (j = 0; len; len--, j++)
				list[count][j] = str[i - len];
			list[count][j] = '\0';
			count++;
			if (!str[i])
			{
				list[count] = NULL;
				return (list);
			}
		}
		else if (str[i] != delim[0])
			len++;
	}
	return (NULL);
}
