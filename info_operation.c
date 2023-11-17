#include "shell.h"

/**
 * clear_command - initializes info_t struct
 * @info: struct
 *
 * Return: void
 * void clear_info(info_t *info)
 **/
void clear_command(info_t *info)
{
	info->argument = NULL;
	info->argument_vector = NULL;
	info->command_path = NULL;
	info->argument_count = 0;
}
/**
 * set_command - initialize struct
 * @info: struct
 * @av: argument vector
 *
 * Return: void
 **/
void set_command(info_t *info, char **av)
{
	int i = 0;

	info->file_name = av[0];
	if (info->argument)
	{
		info->argument_vector = strtow(info->argument, " \t");
		if (!info->argument_vector)
		{
			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->argument_vector[0] = _strdup(info->argument);
				info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
			;
		info->argument_count = i;
		replace_commandalias(info);
		replace_commandvariables(info);
	}
}
/**
 * free_command - frees info_t struct
 * @info: param
 * @all: frees all
 *
 * Return: void
 **/
void free_command(info_t *info, int all)
{
	free_alloc(info->argument_vector);
	info->argument_vector = NULL;
	info->command_path = NULL;
	if (all)
	{
		if (!info->buffer_pointer)
			free(info->argument);
		if (info->environment)
			_freestring(&(info->environment));
		if (info->command_history)
			_freestring(&(info->command_history));
		if (info->command_alias)
			_freestring(&(info->command_alias));
		free_alloc(info->custom_environment);
			info->custom_environment = NULL;
		bfree((void **)info->buffer_pointer);
		if (info->read_file > 2)
			close(info->read_file);
		_putchar(FLUSH_BUFFER);
	}
}
