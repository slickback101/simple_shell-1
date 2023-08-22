#include "shell.h"

/**
 * _myenv - prints the current environ
 * @info: structure containing potential argument.
 * Used to maintain constant function prototype
 * Return: 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: structure containing potential arg.
 * Used to maintain
 * @name: env var name
 *
 * Return: the value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environ variable,
 * or modify an existing one
 * @info: structure containing potential arguments.
 * Used to maintain constnt function prototype.
 * Return: 0 always
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("incorrect num of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - remove an environ variable
 * @info: structure containing potential arguments.
 * Uswed to maintain constant function prototype.
 * Return: 0 always
 */

int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates environ linked list
 * @info: structure containing potential arguments.
 * Used to maintain constant function prototype
 * Return: 0 always
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ, environ[i], 0);
	info->env = nodde;

	return (0);
}
