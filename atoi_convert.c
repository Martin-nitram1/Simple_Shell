#include "shell.h"
/**
 * interactive_mode - check if in interactrive mode
 * @info: param
 *
 * Return: 1 if true otherwise 0
 **/
int interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfile == 0);
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
		{
		if (*delim++ == c)
			return (1);
		}
	return (0);
}
/**
 * _isalphabetic - is alphanumeric?
 * @c: char to check
 *
 * Return: 1 if true, 0 otherwise
 **/
int _isalphabetic(int c)
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
	int m, sig = 1, wave = 0, out;
	unsigned int res = 0;

	for (m = 0; s[m] != '\0' && wave != 2; m++)
	{
		if (s[m] == '-')
			sig *= -1;
		if (s[m] >= '0' && s[m] <= '9')
		{
			wave = 1;
			res *= 10;
			res += (s[m] - '0');
		}
		else if (wave == 1)
			wave = 2;
	}
	if (sig == -1)
		out = -res;
	else
		out = res;
	return (out);
}
