#include "shell.h"

/**
 * input_buf - chained commands
 * @info: param struct
 * @buf: buffer
 * @len: len var
 *
 * Return: bytes read
 **/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
		}
	}
	return (r);
}
/**
 * get_input - get ine minus newline
 * @info: param
 *
 * Return: bytes read
 **/
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
			{
				if (is_chain(info, buf, &j))
					break;
				j++;
			}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = buf;
		return (r);
	}
}
/**
 * read_buf - read buffer
 * @info: param
 * @buf: buffer
 * @i: size
 *
 * Return: int
 **/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t rs = 0;

	if (*i)
		return (0);
	rs = read(info->readfd, buf, READ_BUF_SIZE);
	if (rs >= 0)
		*i = rs;
	return (rs);
}
/**
 * _getline - get next line
 * @info: param
 * @ptr: ptr to buffer
 * @length: dsize of buff
 *
 * Return: r
 **/
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t iq, len;
	size_t k;
	ssize_t rs = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (iq == len)
		iq = len = 0;

	rs = read_buf(info, buf, &len);
	if (rs == -1 || (rs == 0 && len == 1))
		return (-1);
	c = _strchr(buf + 1, '\n');
	k = c ? 1 + (c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + iq, k - iq);
	else
		_strncpy(new_p, buf + iq, k - iq + 1);
	s += k - iq;
	iq = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * sigintHandler - blocks ctr-c
 * @sig_num: signal
 *
 * Return: void
 **/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
