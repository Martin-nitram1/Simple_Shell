#include "shell.h"

/**
 * _myhistory - display hist list
 * @info: param
 *
 * Return: 0 always
 **/
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - set alias to string
 * @info: param
 * @str: string alias
 *
 * Return: 0 always 1 on error
 **/
int unset_alias(info_t *info, char *str)
{
	char *j, c;
	int rit;

	j = _strchr(str, '=');
	if (!j)
		return (1);
	c = *j;
	*j = 0;
	rit = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*j = c;
	return (rit);
}
/**
 * set_alias - set alias to string
 * @info: param
 * @str: string alias
 *
 * Return: 0 on success 1 on error
 **/
int set_alias(info_t *info, char *str)
{
	char *c;

	c = _strchr(str, '=');
	if (!c)
		return (1);
	if (!*++c)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - prints an alias string
 * @node: alias node
 *
 * Return: 0 always 1 on error
 **/
int print_alias(list_t *node)
{
	char *c = NULL, *b = NULL;

	if (node)
	{
		c = _strchr(node->str, '=');
		for (b = node->str; b <= c; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(c + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - alias built in clone
 * @info: param
 *
 * Return: 0 always
 **/
int _myalias(info_t *info)
{
	int j = 0;
	char *c = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (j = 1; info->argv[j]; j++)
	{
		c = _strchr(info->argv[j], '=');
		if (c)
			set_alias(info, info->argv[j]);
		else
			print_alias(fnode_starts_with(info->alias, info->argv[j], '=');
	}
	return (0);
}
