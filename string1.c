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
	int i = 0;

	if (dest == src || src == 0;)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
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
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}
/**
 * _puts - prints a string
 * @str: string to print
 *
 * Return: void
 **/
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
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
	static int i;

	static char buf(WRITE_BUF_SIZE);

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
