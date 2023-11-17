#include "shell.h"

/**
 * displayhistory - display hist list
 * @info: param
 *
 * Return: 0 always
 **/
int displayhistory(info_t *info)
{
	print_liststrings(info->command_history);
	return (0);
}
/**
 * unsetalias - set alias to string
 * @info: param
 * @str: string alias
 *
 * Return: 0 always 1 on error
 **/
int unsetalias(info_t *info, char *str)
{
	char *j, c;
	int rit;

	j = _strchr(str, '=');
	if (!j)
		return (1);
	c = *j;
	*j = 0;
	rit = delete_stringindex(&(info->command_alias),
		node_index(info->command_alias,
		find_nodeprefix(info->command_alias, str, -1)));
	*j = c;
	return (rit);
}
/**
 * setalias - set alias to string
 * @info: param
 * @str: string alias
 *
 * Return: 0 on success 1 on error
 **/
int setalias(info_t *info, char *str)
{
	char *c;

	c = _strchr(str, '=');
	if (!c)
		return (1);
	if (!*++c)
		return (unsetalias(info, str));

	unsetalias(info, str);
	return (string_end(&(info->command_alias), str, 0) == NULL);
}
/**
 * printalias - prints an alias string
 * @node: alias node
 *
 * Return: 0 always 1 on error
 **/
int printalias(list_t *node)
{
	char *c = NULL, *b = NULL;

	if (node)
	{
		c = _strchr(node->text, '=');
		for (b = node->text; b <= c; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(c + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * myalias - alias built in clone
 * @info: param
 *
 * Return: 0 always
 **/
int myalias(info_t *info)
{
	int j = 0;
	char *c = NULL;
	list_t *node = NULL;

	if (info->argument_count == 1)
	{
		node = info->command_alias;
		while (node)
		{
			printalias(node);
			node = node->next;
		}
		return (0);
	}

	for (j = 1; info->argument_vector[j]; j++)
	{
		c = _strchr(info->argument_vector[j], '=');
		if (c)
			setalias(info, info->argument_vector[j]);
		else
			printalias(find_nodeprefix(info->command_alias,
				info->argument_vector[j], '='));
	}
	return (0);
}
