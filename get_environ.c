#include "shell.h"
/**
 * **get_environment - return copy of environ
 * @info: struct
 *
 * Return: 0 always
 **/
char **get_environment(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}
/**
 * _unsetenv - remove env var
 * @info: param
 * @var: string env
 *
 * Return: 1 on delete, 0 otherwise
 **/
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->environment;
	size_t j = 0;
	char *q;

	if (!node || !var)
		return (0);
	while (node)
	{
		q = _startswith(node->str, var);
		if (q && *q == '=')
		{
			info->environment_changed = delete_stringindex(&(info->environment), j);
			j = 0;
			node = info->environment;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->environment_changed);
}
/**
 * _setenv - initialize env var
 * @info: param
 * @var: string var env
 * @value: string env vallue
 *
 * Return: 0n always
 **/
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *q;

	if (!var || !value)
		return (0);
	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->environment;
	while (node)
	{
		q = _startswith(node->text, var);
		if (q && *q == '=')
		{
			free(node->text);
			node->text = buffer;
			info->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->environment), buffer, 0);
	free(buffer);
	info->environment_changed = 1;
	return (0);
}
