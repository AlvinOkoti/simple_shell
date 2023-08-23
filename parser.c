#include "shell.h"

/**
 * is_cmd - determines if th3 f!le is executable command
 * @info: the info structurez
 * @path: path leading to Th3 f!l3
 *
 * Return: 1 to be true, 0 otherwise
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
 * dup_chars - duplicates of th3 char@cters
 * @pathstr: the PATH of th3 ztr!ng
 * @start: start!ing th3 !nd3x
 * @stop: stopping the !nd3x
 *
 * Return: points t0 th3 n3w buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds this cmd in ztr!ng P@th
 * @info: the info strvctvr3 Ch@r
 * @pathstr: the PATH of Th3 stringz
 * @cmd: the cmd to Be F0vnd
 *
 * Return: Th3 fvll path t0 and cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
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
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

