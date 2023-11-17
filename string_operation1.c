#include "shell.h"

/**
 * _strcpy - copy string
 * @dest: destinatin
 * @src: source
 *
 * Return: pointer to destination
 **/
char *_strcpy(char *dest, char *src)
{
	int iq = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[iq])
	{
		dest[iq] = src[iq];
		iq++;
	}
	dest[iq] = 0;
	return (dest);
}
/**
 * _strdup - dups a string
 * @str: the string to dup
 *
 * Return: pointer to the new string
 **/
char *_strdup(const char *str)
{
	int len = 0;
	char *rets;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	rets = malloc(sizeof(char) * (len + 1));
	if (!rets)
		return (NULL);
	for (len++; len--;)
		rets[len] = *--str;
	return (rets);
}
/**
 * _puts - prints a string
 * @str: string to print
 *
 * Return: void
 **/
void _puts(char *str)
{
	int iq = 0;

	if (!str)
		return;
	while (str[iq] != '\0')
	{
		_putchar(str[iq]);
		iq++;
	}
}
/**
 * _putchar - writes char c to stdout
 * @c: char to write
 *
 * Return: 1 on success, -1 on error and errno set
 **/
int _putchar(char c)
{
	static int iq;
	static char buf[BUFFER_SIZE_WRITE];

	if (c == FLUSH_BUFFER || iq >= BUFFER_SIZE_WRITE)
	{
		write(1, buf, iq);
		iq = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[iq++] = c;
	return (1);
}
