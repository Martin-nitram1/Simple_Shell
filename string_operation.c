#include "shell.h"

/**
 * _strlen - five length of string
 * @s: string to check
 *
 * Return: length of string
 **/
int _strlen(char *s)
{
	int ic = 0;

	if (!s)
		return (0);
	while (*s++)
		ic++;
	return (ic);
}
/**
 * _strcmp - compare 2 strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: if s1 < s2 give -1, if s1 > s2 1, 0
 * if s1 == s2
 **/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * starts_with - check if needle starts with haystack
 * @haystack: string to search
 * @needle: substring to fin
 *
 * Return: address of next char of strig or NULL
 **/
char *starts_with(const int *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - concats two strings
 * @dest: dest buffer
 * @src: source buffer
 *
 * Return: pointer to dest
 **/
char *_strcat(char *dest, char *src)
{
	char *rets = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (rets);
}
