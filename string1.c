#include "shell.h"

/**
 * _strcpy - to copy a string
 * @dest: the destination
 * @src: the source
 * Return: the pointer to destination
 */

char _strcpy(char *dest, char *src)
{
	int f = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[f])
	{
		dest[f] = src[f];
		f++;
	}
	dest[f] = 0;
	return (dest);
}

/**
 * _strdup - it duplicates a string
 * @str: the string to be duplicated
 * Return: the pointer to the duplicating string
 */

char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - to print an input string
 * @str: the string to be printed
 * Return: Nothing
 */

void _puts(char *str)
{
	int f = 0;

	if (!str)
		return;
	while (str[f] != '\0')
	{
		_putchar(str[f]);
		f++;
	}
}

/**
 * _putchar - To write the character c to stdout
 * @c: The character to print
 * Return: 1 on Success
 * -1 is returned on error, and errno is set appropriately
 */

int _putchar(char c)
{
	static int f;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || f >= WRITE_BUF_SIZE)
	{
		write(1, buf, f);
		f = 0;
	}
	if (c != BUF_FLUSH)
		buf[f++] = c;
	return (1);
}
