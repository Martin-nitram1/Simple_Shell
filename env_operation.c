#include "shell.h"

/**
 * display_envcmd - print env
 * @info: param
 *
 * Return: 0 always
 **/
int display_envcmd(info_t *info)
{
	print_string(info->environment);
	return (0);
}
/**
 * _getenv - gets value of env var
 * @info: param
 * @name: var env
 *
 * Return: value
 **/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->environment;
	char *c;

	while (node)
	{
		c = _startwith(node->text, name);
		if (c && *c)
			return (c);
		node = node->next;
	}
	return (NULL);
}
/**
 * set_environ - initialize env var
 * @info: param
 *
 * Return: 0 always
 **/
int set_environ(info_t *info)
{
	if (info->argument_count != 3)
	{
		_eputs("Incorrect arguments\n");
		return (1);
	}
	if (_setenv(info, info->argument_vector[1], info->argument_vector[2]))
		return (0);
	return (1);
}
/**
 * unset_environ - remove env var
 * @info: param
 *
 * Return: 0 always
 **/
int unset_environ(info_t *info)
{
	int j;

	if (info->argument_count == 1)
	{
		_eputs("insufficient arguments\n");
		return (1);
	}
	for (j = 1; j < info->argument_count; j++)
		_unsetenv(info, info->argument_vector[j]);
	return (0);
}
/**
 * populate_environ - populate list
 * @info: param
 *
 * Return: 0 always
 **/
int populate_environ(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		string_end(&node, environ[j], 0);
	info->environment = node;
	return (0);
}
