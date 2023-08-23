#include "shell.h"

/**
 * is_cmd - to determine if a file is an executable command
 * @info: the info struct
 * @path: the path to the file
 * Return: 1 if true, otherwise 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - to duplicate characters
 * @pathstr: the Path string
 * @start: the starting index
 * @stop: the stopping index
 * Return: the pointer to new buffer
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int f = 0, g = 0;

	for (g = 0, f = start, f < stop; f++;)
		if (pathstr[f] != ':')
			buf[g++] = pathstr[f];
	buf[g] = 0;
	return (buf);
}

/**
 * find_path - to find cmd in the Path string
 * @info: the info struct
 * @pathstr: the Path string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int f = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[f] || pathstr[f] == ':')
		{
			path = dup_chars(pathstr, curr_pos, f);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[f])
				break;
			curr_pos = f;
		}
		f++;
	}
	return (NULL);
}
