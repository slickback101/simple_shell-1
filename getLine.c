#include "shell.h"

/**
 * input_buf - to buffer chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t c = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left int the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, signtHandler);
#if USE_GETLINE
		c = _getline(buf, &len_p);
#else
		c = _getline(info, buf, &len_p);
#endif
		if (c > 0)
		{
			if ((*buf)[c - 1] == '\n')
			{
				(*buf)[c - 1] = '\0'; /* remove trailing newline */
				c--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, '--)) is this a command chain? */
			{
				*len = c;
				info->cmd_buf = buf;
			}
		}
	}
	return (c);
}

/**
 * get_input - get a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* the '-' command chain buffer */
	static size_t f, g, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		g = f; /* init new iterator to current buf position */
		p = buf + f; /* get pointer for return */

		check_chain(info, buf, &g, f, len);
		while (g < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &g))
				break;
			g++;
		}

		f = f + 1; /* increment past nulled ';" */
		if (f >= len) /* reached end of buffer? */
		{
			f = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *f)
{
	ssize_t r = 0;

	if (*f)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*f = r;
	return (r);
}

/**
 * * _getline - will get the next line of input from STDIN
 * @info: parameter struct
 * @ptr: the address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);

	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * signinHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void signinHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
