#include "shell.h"
/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source of string
 * @n: the amount of characters to be copied
 * Return: the concntenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int f, g;
	char *s = dest;

	f = 0;
	while (src[f] != '\0' && f < n - 1)
	{
		dest[f] = src[f];
		f++;
	}
	if (f < n)
	{
		g = f;
		while (g < n)
		{
			dest[g] = '\0';
			g++;
		}
	}
	return (s);
}

/**
 * _strncat - to concatenate two strings
 * @dest: the first string
 * @src: the second string
 * @n: the maximum amount of bytes to be used
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int f, g;
	char *s = dest;

	f = 0;
	g = 0;
	while (dest[f] != '\0')
		f++;
	while (src[g] != '\0' && g < n)
	{
		dest[f] = src[g];
		f++;
		g++;
	}
	if (g < n)
		dest[f] = '\0';
	return (s);
}

/**
 * _strchr - to locate the character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: (s) the pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

