#include "shell.h"

/**
 * command_chain - test if current char in buffer is a delim
 * @info: param struct
 * @buf: char buffer
 * @p: address of current position in bug
 *
 * Return: 1 if chain delim, 0 if otherwise
 **/
int command_chain(info_t *info, char *buf, size_t  *p)
{
	size_t jk = *p;

	if (buf[jk] == '|' && buf[jk + 1] == '|')
	{
		buf[jk] = 0;
		jk++;
		info->buffer_type = COMMAND_OR;
	}
	else if (buf[jk] == '&' && buf[jk + 1] == '&')
	{
		buf[jk] = 0;
		jk++;
		info->buffer_type = COMMAND_AND;
	}
	else if (buf[jk] == ';')
	{
		buf[jk] = 0;
		info->buffer_type = COMMAND_CHAIN;
	}
	else
		return (0);
	*p = jk;
	return (1);
}
/**
 * check_command - check if continue based on last status
 * @info: param struct
 * @buf: char buf
 * @p: address of position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: void
 **/
void check_command(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t jt = *p;

	if (info->buffer_type == COMMAND_AND)
	{
		if (!info->execution_status)
		{
			buf[i] = 0;
			jt = len;
		}
	}
	if (info->buffer_type == COMMAND_OR)
	{
		if (!info->execution_status)
		{
			buf[i] = 0;
			jt = len;
		}
	}
	*p = jt;
}
/**
 * replace_commandalias - replace alias in tokenized string
 * @info: param struct
 *
 * Return: 1 if replaced, 0 otherwise
 **/
int replace_commandalias(info_t *info)
{
	int iq;
	list_t *node;
	char *p;

	for (iq = 0; iq < 10; iq++)
	{
		node = find_nodeprefix(info->command_alias, info->argument_vector[0], '=');
		if (!node)
			return (0);
		free(info->argument_vector[0]);
		p = _strchr(node->text, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argument_vector[0] = p;
	}
	return (1);
}
/**
 * replace_commandvariables - replace vars in string
 * @info: param struct
 *
 * Return: 1 if replaces, 0 otherwise
 **/
int replace_commandvariables(info_t *info)
{
	int iq = 0;
	list_t *node;

	for (iq = 0; info->argument_vector[iq]; iq++)
	{
		if (info->argument_vector[iq][0] != '$' || !info->argument_vector[iq][1])
			continue;
		if (!_strcmp(info->argument_vector[iq], "$?"))
		{
			replace_substring(&(info->argument_vector[iq]),
					_strdup(convert_to_string(info->execution_status, 10, 0)));
			continue;
		}
		if (!strcmp(info->argument_vector[iq], "$$"))
		{
			replace_substring(&(info->argv[iq]),
					_strdup(convert_to_string(getpid(), 10, 0)));
			continue;
		}
		node = find_nodeprefix(info->env, &info->argv[iq][1], '=');
		if (node)
		{
			replace_substring(&(info->argument_vector[iq]),
				_strdup(_strchr(node->text, '=') + 1));
			continue;
		}
		replace_substring(&info->argument_vector[iq], _strdup(""));
	}
	return (0);
}
/**
 * replace_substring - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 **/
int replace_substring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

