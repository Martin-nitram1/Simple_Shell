#include "shell.ih"

/**
 * is_chain - test if current char in buffer is a delim
 * @info: param struct
 * @buf: char buffer
 * @p: address of current position in bug
 *
 * Return: 1 if chain delim, 0 if otherwise
 **/
int is_chain(info_t *info, char *buf, size_t  *p)
{
	size_t jk = *p;

	if (buf[jk] == '|' && buf[jk + 1] == '|')
	{
		buf[jk] = 0;
		jk++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[jk] == '&' && buf[jk + 1] == '&')
	{
		buf[jk] = 0;
		jk++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[jk] == ';')
	{
		buf[jk] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = jk;
	return (1);
}
/**
 * check_chain - check if continue based on last status
 * @info: param struct
 * @buf: char buf
 * @p: address of position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: void
 **/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t jt = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (!info->status)
		{
			buf[i] = 0;
			jt = len;
		}
	}
	*p = jt;
}
/**
 * replace_alias - replace alias in tokenized string
 * @info: param struct
 *
 * Return: 1 if replaced, 0 otherwise
 **/
int replace_alias(info_t *info)
{
	int iq;
	list_t *node;
	char *p;

	for (iq = 0; iq < 10; iq++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
/**
 * replace_vars - replace vars in string
 * @info: param struct
 *
 * Return: 1 if replaces, 0 otherwise
 **/
int replace_vars(info_t *info)
{
	int iq = 0;
	list_t *node;

	for (iq = 0; info->argv[iq]; iq++)
	{
		if (info->argv[iq][0] != '$' || !info->argv[iq][1])
			continue;
		if (!_strcmp(info->argv[iq], "$?"))
		{
			replace_string(&(info->argv[iq]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!strcmp(info->argv[iq], "$$"))
		{
			replace_string(&(info->argv[iq]),
					strstrdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[iq][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[iq], _strdup(""));
	}
	return (0);
}
/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 **/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

