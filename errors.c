#include "shell.h"

/**
 * _eputs - prints an input strings
 * @str: the string to print
 *
 * Return : void
 **/
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}
/**
 * _eputchar - writes char to stderr
 * @c: char to print
 *
 * Return: 1 on success, -1 on error and errno
 * set appropriately
 **/
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * _putfd - write char to fd
 * @c: char to print
 * @fd: file descriptor
 *
 * Return: 1 on success, -1 on error and errno set
 **/
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * _putsfd - print to input string
 * @str: string to print
 * @fd: file descriptor
 *
 * Return: num of chars
 **/
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putsfd(*str++, fd);
	}
	return (i);
}
