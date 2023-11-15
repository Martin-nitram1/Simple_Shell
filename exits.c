#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: destination
 * @src: source
 * @n: amount of characters
 *
 * Return: concat string
 **/
char *_strncpy(char *dest, char *src, int n)
{
	int j, b;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' &&  j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < n)
	{
		b = j;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}
/**
 * *_strncat - concatenates 2 strings
 * @dest: string 1
 * @src: string 2
 * @n: amount of bytes
 *
 * Return: concat strings
 **/
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}
/**
 * _strchr - locates character in string
 * @s: string to parse
 * @c: character to locate
 *
 * Return: pointer to teh memory
 **/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
