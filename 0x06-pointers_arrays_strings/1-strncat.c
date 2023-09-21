#include "main.h"

/**
 * _strncat - Concatenates two strings usinginputted number from src
 * @src: pointer to string to be appended to dest.
 * @n: The number of bytes from src to be appended to dest.
 * @dest: pointer to destination tobe appended upon.
 *
 * Return: A pointer to the resulting string dest.
 */

char *_strncat(char *dest, char *src, int n)
{
	int aray = 0, d_count = 0;

	while (dest[aray++])
	{
		d_count++;
	}

	for (aray = 0; src[aray] && aray < n; aray++)
	{
		dest[d_count++] = src[aray];
	}

	return (dest);
}
