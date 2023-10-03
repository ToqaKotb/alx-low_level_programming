#include <stdio.h>
#include "main.h"

/**
 * main - prints the program name
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: Always 0
 */

int main(int argc, char *argv[])
{
	print("%s\n", *argv);

	return (0);
}
