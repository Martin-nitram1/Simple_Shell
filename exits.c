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
	char *s = dest;

	while (*src && n-- > 0)
		{
			*dest++ = *src++;
		}
	*dest = '\0';
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
char *_strncat(char *dest, char *src, __attribute__((unused))int n)
{
	char *s = dest;

	while (*dest)
		{
			*dest++ = *src++;
		}
	*dest = '\0';
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
	while (*s != '\0')
		{
			if (*s == c)
			{
				return (s);
			}
			s++;
		}
	return (NULL);
}
