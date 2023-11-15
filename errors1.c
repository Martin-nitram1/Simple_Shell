#include "shell.h"

/**
 * _erratoi - convert string to int
 * @s: string convert
 *
 * Return:  0 if success -1 if error
 **/
int _erratoi(char *s)
{
	int f = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (f = 0; s[f] != '\0'; f++)
	{
		if (s[f] >= '0' && s[f] <= '9')
		{
			res *= 10;
			res += (s[f] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
/**
 * print_error - print error message
 * @info: param
 * @estr: error type
 *
 * Return: void
 **/
void print_error(into_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * print_d - prints decimal
 * @input: the input
 * @fd: file descriptor
 *
 * Return: nums of chars
 **/
int print_d(int input, int fd)
{
	int (*_putchar)(char) = _putchar;
	int e, count = 0;
	unsigned int abs, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		abs = _input;
		__putchar('-');
		count++;
	}
	else
		abs = input;
	curr = abs;
	for (e = 1000000000; e > 1; e /= 10)
	{
		if (abs / e)
		{
			__putchar('0' + curr / e);
			count++;
		}
		curr %= e;
	}
	__putchar('0' + curr);
	count++;
	return (count);
}
/**
 * *convert_number - convert
 * @num: number
 * @base: base
 * @flags: arg flag
 *
 * Return: string
 **/
char *convert_number(long int num, int base, int flags)
{
	static char *ray;
	static char buffer[50];
	char sig = 0;
	char *ptr;
	unsigned long i = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sig = '-';
	}
	ray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	while (n != 0)
	{
		*--ptr = ray[n % base];
		n /= base;
	}
	if (sig)
		*--ptr = sig;
	return (ptr);
}
/**
 * remove_comments - replace '#' with '\0'
 * @buf: address of string to checck
 *
 * Return: 0 always
 **/
void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
	{
		if (buf[j] == '#' && (!j || buf[j + 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
	}
}
