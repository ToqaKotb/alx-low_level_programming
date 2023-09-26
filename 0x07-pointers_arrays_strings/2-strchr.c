#include "main.h"
#include <stdio.h>

/**
 * _strchr - locates a caracter in a string
 * @s: string to search
 * @c: character to locatr
 * Return: null
 */


char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
		{
			return (s + i);
		}
	}

	return (NULL);
}
