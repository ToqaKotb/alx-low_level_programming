#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "main.h"
/**
 * read_textfile - reads textfile to print to stdout
 * @filename: input textfile
 * @letters: size of textfile
 * Return: elements read and printed
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	char *buff;
	ssize_t fd, rd, wr;

	if (filename == NULL)
		return (0);

	buff = malloc(sizeof(char) * letters);
	if (buff == NULL)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(buff);
		return (0);
	}

	rd = read(fd, buff, letters);
	if (rd == -1)
	{
		free(buff);
		return (0);
	}

	wr = write(STDOUT_FILENO, buff, rd);
	if (wr == -1)
	{
		free(buff);
		return (0);
	}

	free(buff);
	close(fd);

	return (wr);
}
