#include "shell.h"

/**
 * _eputs - to print and input strings
 * @str: the string to be printed
 * Return: nothing
 */
void _eputs(char *str)
{
	int e = 0;

	if (!str)
		return;
	while (str[e] != '\0')
	{
		_eputchar(str[e]);
		e++;
	}
}

/**
 * _eputchar - to write the character c to stderr
 * @c: The character to be printed
 * Return: 1 on success
 * On error, -1 is returned and errno is set
 */
int _eputchar(char c)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(2, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

/**
 * _putfd - writes the character to be given fd
 * @c: The character to be printed
 * @fd: The file descriptor to write to
 * Return: 1 on success
 * On error, -1 is returned and errno is set
 */
int _putfd(char c, int fd)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(fd, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

/**
 * _putsfd - to print an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int e = 0;

	if (!str)
		return (0);
	while (*str)
	{
		e += _putfd(*str++, fd);
	}
	return (e);
}
