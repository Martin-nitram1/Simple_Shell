#include "shell.h"

/**
 * _myenv - print env
 * @info: param
 *
 * Return: 0 always
 **/
int _myenv(info_t *info)
{
	print_list_str(info->env);
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
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
		return (p);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - initialize env var
 * @info: param
 *
 * Return: 0 always
 **/
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2];))
		return (0);
	return (1);
}
/**
 * _myunsetenv - remove env var
 * @info: param
 *
 * Return: 0 always
 **/
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("insufficient arguments\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);
	return (0);
}
/**
 * populate_env_list - populate list
 * @info: param
 *
 * Return: 0 always
 **/
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
