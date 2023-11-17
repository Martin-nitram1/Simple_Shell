#include "shell.h"

/**
 * is_cmd - check if file is  a command
 * @info: info struct
 * @path: path to file
 *
 * Return: 1 if true, otherwise 0
 **/
int is_cmd(info_t *info, char *path)
{
	struct stat star;
	(void)info;

	if (!path || stat(path, &star))
		return (0);

	if (star.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * *dup_chars - dups chars
 * @pathstr: path string
 * @start: start index
 * @stop: stop index
 *
 * Return: pointer to new buf
 **/
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int iq = 0, ks = 0;

	for (ks = 0, iq = start; iq < stop; iq++)
		if (pathstr[iq] != ':')
			buf[ks++] = pathstr[iq];
	buf[ks] = 0;
	return (buf);
}
/**
 * find_path - finds command in path
 * @info: info struct
 * @pathstr: path string
 * @cmd: command string
 *
 * Return: full path if found or NULL
 **/
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int iq = 0, currpos = 0;
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
		if (!pathstr[iq] || pathstr[iq] == ':')
		{
			path = dup_chars(pathstr, currpos, iq);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[iq])
				break;
			currpos = iq;
		}
		iq++;
	}
	return (NULL);
}
