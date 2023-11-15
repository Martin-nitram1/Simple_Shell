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
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' &&  i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
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
	} while (*ss++ != '\0');
	return (NULL);
}
