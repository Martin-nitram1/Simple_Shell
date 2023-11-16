#include "shell.h"

/**
 * *_memset - fillls memory with a constant byte
 * @s: pointer to memeory area
 * @b: byte ti fill s with
 * @n: amount of bytes to be filled
 * Return: pointer to memory
 **/
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int is;

	for (is = 0; is < n; is++)
		s[is] = b;
	return (s);
}
/**
 * ffree - frees a string memory
 * @pp: the string
 *
 * Return: void
 **/
void ffree(char **pp)
{
	char **ab = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(ab);
}
/**
 * _realloc - rellocates a memory block
 * @ptr: pointer to previous block
 * @old_size: previous block
 * @new_size: new block
 *
 * Return: pointer to memory allocd
 **/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pa = NULL;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		pa[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pa);
}
