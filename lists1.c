#include "shell.h"

/**
 * list_len - will determine the length of linked list
 * @h: pointer to the first node
 * Return: size of the list
 */
size_t list_len(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * list_to_string - returns an array of strings of the list->str
 * @head: the pointer to first node
 * Return: array of the strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t l = list_len(head), m;
	char **strs;
	char *str;

	if (!head || !l)
		return (NULL);
	strs = malloc(sizeof(char *) * (l + 1));
	if (!strs)
		return (NULL);
	for (l = 0; node; node = node->next, l++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (m = 0; m < l; m++)
				free(strs[m]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[l] = str;
	}
	strs[l] = NULL;
	return (strs);
}

/**
 * print_list - will print all elements of a list_t linked list
 * @h: pointer to first node
 * Return: the size of list
 */
size_t print_list(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nill)");
		_puts("\n");
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list the head
 * @prefix: the string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - to get the index of a node
 * @head: the pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t h = 0;

	while (head)
	{
		if (head == node)
			return (h);
		head = head->next;
		h++;
	}
	return (-1);
}
