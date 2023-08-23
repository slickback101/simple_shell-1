#include "shell.h"
/**
 * is_chain - test if the current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf:the char buffer
 * @p: address of current posotion in buf
 * Return: if chain delimete 1, 0 othereie
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t g = *p;

	if (buf[g] == '|' && buf[g + 1] == '|')
	{
		buf[g] = 0;
		g++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[g] == '&' && buf[g + 1] == '&')
	{
		buf[g] = 0;
		g++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[g] == ';') /* found end of this command */
	{
		buf[g] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = g;
	return (1);
}

/**
 * check_chain - to check if we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t f, size_t len)
{
	size_t g = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[f] = 0;
			g = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[f] = 0;
			g = len;
		}
	}

	*p = g;
}

/**
 * replace_alias - to replace an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alais(info_t *info)
{
	int f;
	list_t *node;
	char *p;

	for (f = 0; f < 10; f++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - to replace vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int f = 0;
	list_t *node;

	for (f = 0; info->argv[f]; f++)
	{
		if (info->argv[f][0] != '$' || !info->argv[f][1])
			continue;
		if (!_strcmp(info->argv[f], "$?"))
		{
			replace_string(&(info->argv[f]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[f], "$$"))
		{
			replace_string(&(info->argv[f]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[f][1], '=');
		if (node)
		{
			replace_string(&(info->argv[f]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[f], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - to replace the string
 * @old: address to the old string
 * @new: the new string
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
