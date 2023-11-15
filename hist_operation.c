#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: param
 *
 * Return: allocated string
 **/
char *get_history_file(info_t *info)
{
	char *bufs, *dirs;

	dirs = _getenv(info, "HOME=");
	if (!dirs)
		return (NULL);
	bufs = malloc(sizeof(char) * (_strlen(dirs) + _strlen(HIST_FILE) + 2));
	if (!bufs)
		return (NULL);
	bufs[0] = 0;
	_strcpy(bufs, dirs);
	_strcat(bufs, "/");
	_strcat(bufs, HIST_FILE);
	return (bufs);
}
/**
 * write_history - creates a file, or appends to an existing file
 * @info: param
 *
 * Return: 1 on success otherwise -1
 **/
int write_history(info_t *info)
{
	ssize_t fd;
	char *file_name = get_history_file(info);
	list_t *nodes = NULL;

	if (!file_name)
		return (-1);
	fd = open(file_name, 0_CREATE | 0_TRUNC | 0_RDWR, 0644);
	free(file_name);
	if (fd == -1)
		return (-1);
	for (nodes = info->history; nodes; nodes = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_history - read from history file
 * @info: param
 *
 * Return: histcount on success 0 otherwise
 **/
int read_history(info_t *info)
{
	int iq, last = 0, line_count = 0;
	ssize_t fd, rd_len, fsize = 0;
	struct stat st;
	char *buf = NULL, *file_name = get_history_file(info);

	if (!file_name)
		return (0);

	fd = open(file_name, 0_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rd_len = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rd_len <= 0)
		return (free(buf), 0);
	close(fd);
	for (iq = 0; iq < fsize; iq++)
		if (buf[iq] == '\n')
		{
			buf[iq] = 0;
			build_history_list(info, buf + last, line_count++);
			last = iq + 1;
		}
	if (last != iq)
		build_history_list(info, buf + last, line_count++);
	free(buf);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - adds entry
 * @info: strct
 * @buf: buffer
 * @linecount: history linecount
 *
 * Return: 0 always
 **/
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nodes = NULL;

	if (info->history)
		nodes = info->history;
	add_node_end(&nodes, buf, linecount);
	if (!info->history)
		info->history = nodes;
	return (0);
}
/**
 * renumber_history - renumbers history
 * @info: structure
 *
 * Return: new histcount
 **/
int renumber_history(info_t *info)
{
	list_t *nodes = info->history;
	int i = 0;

	while (nodes)
	{
		nodes->num = i++;
		nodes = node->next;
	}
	return (info->histcount = i);
}
