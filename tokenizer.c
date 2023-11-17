#include "shell.h"

/**
 * **strtow - split strig to words
 * @str: input
 * @d: delim string
 *
 * Return: pointer to string or NULL if failed
 **/
char **strtow(char *str, char *d)
{
	int is, jk, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (is = 0; str[is] != '\0'; is++)
		if (!is_delim(str[is], d) && (is_delim(str[is + 1], d) || !str[1 + 1]))
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (is = 0, jk = 0; jk < numwords; jk++)
	{
		while (is_delim(str[is], d))
			is++;
		k = 0;
		while (!is_delim(str[is + k], d) && str[is + k])
			k++;
		s[jk] = malloc((k + 1) * sizeof(char));
		if (!s[jk])
		{
			for (k = 0; k < jk; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[jk][m] = str[is++];
		s[jk][m] = 0;
	}
	s[jk] = NULL;
	return (s);
}
/**
 * **strtow2 - split string to words
 * @str: input
 * @d: delim
 *
 * Return: pointer to string array or NULL if fail
 **/
char **strtow2(char *str, char d)
{
	int i, j, m, numwords = 0;
	int k = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	}
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] !=d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m <k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
