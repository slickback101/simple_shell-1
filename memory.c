#include "shell.h"

/**
 * bfree - to free a pointer and NULL the address
 * @ptr: address of the pointer to be free
 * Return: 1 if free, 0 otherwise
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
