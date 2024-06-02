#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * _elfchecker - checks if file is ELF file
 * @h: elf header file
 * Return: void
 */
void _elfchecker(unsigned char *h)
{
	if (h[0] != 0x7f && h[1] != 'E' && h[2] != 'L' && h[3] != 'F')
	{
		dprintf(STDERR_FILENO, "Not an ELF file\n");
		exit(98);
	}

	printf("ELF Header:\n");
}
/**
 * _printmagic - prints magic number
 * @h: elf header file
 * Return: void
 */
void _printmagic(unsigned char *h)
{
	int idx = 0;

	printf("  Magic:   ");

	while (idx < EI_NIDENT)
	{
		printf("%02x", h[idx]);
		if (idx < EI_NIDENT - 1)
			printf(" ");
		else
			printf("\n");

		idx++;
	}
}
/**
 * _printclass - prints architecture
 * @h: elf header file
 * Return: void
 */
void _printclass(unsigned char *h)
{
	printf("  Class:                             ");

	if (h[4] == ELFCLASS32)
		printf("ELF32\n");
	else if (h[4] == ELFCLASS64)
		printf("ELF64\n");
	else
		printf("Invalid Class\n");
}
/**
 * _printdata - prints data encoding of the machine
 * @h: elf header file
 * Return: void
 */
void _printdata(unsigned char *h)
{
	printf("  Data:                              ");

	if (h[5] == ELFDATA2LSB)
		printf("2's complement, little endian\n");
	else if (h[5] == ELFDATA2MSB)
		printf("2's complement, big endian\n");
	else
		printf("Unknown data format\n");
}
/**
 * _printversion - prints version number of elf-file
 * @h: elf header file
 * Return: void
 */
void _printversion(unsigned char *h)
{
	printf("  Version:                           ");

	if (h[6] == EV_CURRENT)
		printf("1 (current)\n");
	else if (h[6] == EV_NONE)
		printf("Invalid version\n");
}
/**
 * _printosabi - prints OS and ABI
 * @h: elf header file
 * Return: void
 */
void _printosabi(unsigned char *h)
{
	printf("  OS/ABI:                            ");

	if (h[7] == ELFOSABI_NONE)
		printf("UNIX - System V\n");
	else if (h[7] == ELFOSABI_HPUX)
		printf("UNIX - HP-UX\n");
	else if (h[7] == ELFOSABI_NETBSD)
		printf("UNIX - NetBSD\n");
	else if (h[7] == ELFOSABI_LINUX)
		printf("UNIX - Linux\n");
	else if (h[7] == ELFOSABI_SOLARIS)
		printf("UNIX - Solaris\n");
	else if (h[7] == ELFOSABI_IRIX)
		printf("UNIX - IRIX\n");
	else if (h[7] == ELFOSABI_FREEBSD)
		printf("UNIX - FreeBSD\n");
	else if (h[7] == ELFOSABI_TRU64)
		printf("UNIX - TRU64\n");
	else if (h[7] == ELFOSABI_ARM)
		printf("ARM\n");
	else if (h[7] == ELFOSABI_STANDALONE)
		printf("Stand-alone (embedded)\n");
	else
		printf("<unknown: %x\n>", h[7]);
}
/**
 * _printabiversion - prints ABI version No.
 * @h: elf header file
 * Return: void
 */
void _printabiversion(unsigned char *h)
{
	printf("  ABI Version:                       ");
	printf("%x\n", h[8]);
}
/**
 * _printtype - prints obj file-type
 * @type: elf header file
 * @h: elf header file
 * Return: void
 */
void _printtype(uint16_t type, unsigned char *h)
{
	if (h[5] == ELFDATA2MSB)
		type >>= 8;

	printf("  Type:                              ");

	if (type == ET_NONE)
		printf("NONE (None)\n");
	else if (type == ET_REL)
		printf("REL (Relocatable file)\n");
	else if (type == ET_EXEC)
		printf("EXEC (Executable file)\n");
	else if (type == ET_DYN)
		printf("DYN (Shared object file)\n");
	else if (type == ET_CORE)
		printf("CORE (Core file)\n");
	else
		printf("<unknown: %x>\n", type);
}
/**
 * _printentrypoint - prints elf file entry point
 * @entry: elf header file
 * @h: elf header file
 * Return: void
 */
void _printentrypoint(unsigned int entry, unsigned char *h)
{
	printf("  Entry point address:               ");

	if (h[5] == ELFDATA2MSB)
	{
		entry = ((entry << 8) & 0xFF00FF00) | ((entry >> 8) & 0xFF00FF);
		entry = (entry << 16) | (entry >> 16);
	}

	if (h[4] == ELFCLASS32)
		printf("%#x\n", entry);
	else
		printf("%#x\n", entry);
}
/**
 * _safeclose - closes a file descriptor
 * @open: file descriptor
 * Return: void
 */
void _safeclose(int open)
{
	if (close(open) == -1)
	{
		dprintf(STDERR_FILENO, "Cannot close file\n");
		exit(98);
	}
}
/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	Elf64_Ehdr elf_h[32];
	int fd_op;

	if (ac != 2)
	{
		printf("Usage: %s elf-file\n", av[0]);
		exit(98);
	}

	fd_op = open(av[1], O_RDONLY);
	if (read(fd_op, elf_h, 32) == -1)
	{
		dprintf(STDERR_FILENO, "Cannot read file %s\n", av[1]);
		_safeclose(fd_op);
		exit(98);
	}

	_elfchecker(elf_h->e_ident);
	_printmagic(elf_h->e_ident);
	_printclass(elf_h->e_ident);
	_printdata(elf_h->e_ident);
	_printversion(elf_h->e_ident);
	_printosabi(elf_h->e_ident);
	_printabiversion(elf_h->e_ident);
	_printtype(elf_h->e_type, elf_h->e_ident);
	_printentrypoint(elf_h->e_entry, elf_h->e_ident);

	_safeclose(fd_op);
	return (0);
}
