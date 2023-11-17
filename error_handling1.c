#include "shell.h"

/**
 * _eatoi - convert string to int
 * @s: string convert
 *
 * Return:  0 if success -1 if error
 **/
int _eatoi(char *s)
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
void _error(info_t *info, char *estr)
{
	_eputs(info->file_name);
	_eputs(": ");
	print_d(info->line_number, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argument_vector[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * printd - prints decimal
 * @input: the input
 * @fd: file descriptor
 *
 * Return: nums of chars
 **/
int printd(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int e, count = 0;
	unsigned int abs, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		abs = -input;
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
 * *convert_to_string - convert
 * @num: number
 * @base: base
 * @flags: arg flag
 *
 * Return: string
 **/
char *convert_to_string(long int num, int base, int flags)
{
	static char *ray;
	static char buffer[50];
	char sig = 0;
	char *ptr;
	unsigned long i = num;

	if (!(flags & TO_UNSIGNED) && num < 0)
	{
		i = -num;
		sig = '-';
	}
	ray = flags & TO_LOWER_CASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	while (i != 0)
	{
		*--ptr = ray[i % base];
		i /= base;
	}
	if (sig)
		*--ptr = sig;
	return (ptr);
}
/**
 * remove_comlines - replace '#' with '\0'
 * @buf: address of string to checck
 *
 * Return: 0 always
 **/
void remove_comlines(char *buf)
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
