#include "shell.h"

/**
 * add_node - add node to start
 * @head: head node
 * @str: str field
 * @num: node index
 *
 * Return: size of list
 **/
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *newhead;

	if (!head)
		return (NULL);
	newhead = malloc(sizeof(list_t));
	if (!newhead)
		return (NULL);
	_memset((void *)newhead, 0, sizeof(list_t));
	newhead->num = num;
	if (str)
	{
		newhead->str = _strdup(str);
		if (!newhead->str)
		{
			free(newhead);
			return (NULL);
		}
	}
	newhead->next = *head;
	*head = newhead;
	return (newhead);
}
/**
 * add_node_end - add node at end
 * @head: head node
 * @str: str field
 * @num: number
 *
 * Return: node index
 **/
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *newnode, *node;

	if (!head)
		return (NULL);
	node = *head;
	newnode = malloc(sizeof(list_t));
	if (!newnode)
		return (NULL);
	_memset((void *)newnode, 0, sizeof(list_t));
	newnode->num = num;
	if (str)
	{
		newnode->str = _strdup(str);
		if (!newnode->str)
		{
			free(newnode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newnode;
	}
	else
		*head = newnode;
	return (newnode);
}
/**
 * print_list_str - print str elements
 * @h: pointer to head
 *
 * Return: size of list
 **/
size_t print_list_str(const list_t *h)
{
	size_t iq = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		iq++;
	}
	return (iq);
}
/**
 * delete_node_at_index - delets node at index
 * @head: head node
 * @index: index to check
 *
 * Return: 1 if success, otherwise 0
 **/
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nodes, *prevnode;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		nodes = *head;
		*head = (*head)->next;
		free(nodes->str);
		free(nodes);
		return (1);
	}
	nodes = *head;
	while (nodes)
	{
		if (i == index)
		{
			prevnode->next = nodes->next;
			free(nodes->str);
			free(nodes);
			return (1);
		}
		i++;
		prevnode = nodes;
		nodes = nodes->next;
	}
	return (0);
}
/**
 * free_list - frees all nodes
 * @head_ptr: head node
 *
 * Return:  void
 **/
void free_list(list_t **head_ptr)
{
	list_t *nodes, *nextnode, *heads;

	if (!head_ptr || !*head_ptr)
		return;
	heads = *head_ptr;
	nodes = heads;
	while (nodes)
	{
		nextnode = nodes->next;
		free(nodes->str);
		free(nodes);
		nodes = nextnode;
	}
	*head_ptr = NULL;
}
