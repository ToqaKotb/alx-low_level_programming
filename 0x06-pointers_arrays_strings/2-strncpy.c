#include "main.h"

/**
 * _strncpy - Copies a number of bytes from string src into dest
 * @n: number of bytes to copied from src
 * @dest: Destination of the pointer to the string
 * @src: Source of the pointer to the string to copy
 * Return: Pointer to the destination string.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; src[i] != '\0' && i < n; i++)
		dest[i]	= src[i];
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}
