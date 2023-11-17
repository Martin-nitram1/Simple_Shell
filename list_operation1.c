#include "shell.h"

/**
 * _stringlen - check length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 **/
size_t _stringlen(const list_t *h)
{
	size_t is = 0;

	while (h)
	{
		h = h->next;
		is++;
	}
	return (is);
}
/**
 * list_strings - returns array
 * @head: head node
 *
 * Return: array of strings
 **/
char **list_strings(list_t *head)
{
	list_t *nodes = head;
	size_t i = _stringlen(head), j;
	char **str_s;
	char *str;

	if (!head || !i)
		return (NULL);
	str_s = malloc(sizeof(char *) * (i + 1));
	if (!str_s)
		return (NULL);
	for (i = 0; nodes; nodes = nodes->next, i++)
	{
		str = malloc(_strlen(nodes->text) + 1);
		if (!str)
		{
			for (j = 0; j < 1; j++)
				free(str_s[j]);
			free(str_s);
			return (NULL);
		}
		str = _strcpy(str, nodes->text);
		str_s[i] = str;
	}
	str_s[i] = NULL;
	return (str_s);
}
/**
 * print_liststrings - prints elements
 * @h: pointer to first node
 *
 * Return: size pof list
 **/
size_t print_liststrings(const list_t *h)
{
	size_t iq = 0;

	while (h)
	{
		_puts(convert_to_string(h->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->text ? h->text : "(nil)");
		_puts("\n");
		h = h->next;
		iq++;
	}
	return (iq);
}
/**
 * find_nodeprefix - check if strig  starts with index
 * @node: pointer to list head
 * @prefix: string tpo match
 * @c: next character
 *
 * Return: match node or NULL
 **/
list_t *find_nodeprefix(list_t *node, char *prefix, char c)
{
	char *ps = NULL;

	while (node)
	{
		ps = _startwith(node->text, prefix);
		if (ps && ((c == -1) || (*ps == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * node_index- gets the index of a node
 * @head: head node
 * @node: pointer to node
 *
 * Return: index of node or -1
 **/
ssize_t node_index(list_t *head, list_t *node)
{
	size_t iq = 0;

	while (head)
	{
		if (head == node)
			return (iq);
		head = head->next;
		iq++;
	}
	return (-1);
}
