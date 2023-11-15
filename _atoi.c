#include "shell.h"
/**
 * interactive - check if in interactrive mode
 * @info: param
 *
 * Return: 1 if true otherwise 0
 **/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - check if delimiter
 * @c: char to check
 * @delim: delim string
 *
 * Return: 1 if true 0 if false
 **/
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * _isalpha - is alphanumeric?
 * @c: char to check
 *
 * Return: 1 if true, 0 otherwise
 **/
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - convert string to integer
 * @s: string to convert
 *
 * Return: 0 if no num in string, otherwise
 * converted number
 **/
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] = '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
