#include "shell.h"

/**
 * interactive - returns True if shell is interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 if otherwise
 */
int intetactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @b: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */

int is_delim(char b, char *delim)
{
	while (*delim)
		if (*delim++ == b)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @b: The character to be input
 * Return: 1 is b alphabetic, 0 otherwise
 */

int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - to convert a string to an interger
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number if otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
