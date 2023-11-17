#include "shell.h"

/**
 * custom_shell -  main loop for the shell
 * @info: param
 * @av: the argument vector
 *
 * Return: 0 if success 1 if fail and err no
 **/
int custom_shell(info_t *info, char **av)
{
	ssize_t r = 0;
	int build = 0;

	while (r != -1 && build != -2)
	{
		clear_command(info);
		if (interactive_mode(info))
			_puts("$ ");
		_eputchar(FLUSH_BUFFER);
		r = read_input(info);
		if (r != -1)
		{
			set_command(info, av);
			build = identify_builtin(info);
			if (build == -1)
				find_command(info);
		}
		else if (interactive_mode(info))
			_putchar('\n');
		free_command(info, 0);
	}
	write_hist(info);
	free_command(info, 1);
	if (!interactive_mode(info) && info->execution_status)
		exit(info->execution_status);
	if (build == -2)
	{
		if (info->error_number == -1)
			exit(info->execution_status);
		exit(info->error_number);
	}
	return (build);
}
/**
 * identify_builtin - finds builtin command
 * @info: param
 *
 * Return: -1 if not found, 0 if executed success,
 * 1 if found but not executed, -2 if signal exits
 **/
int identify_builtin(info_t *info)
{
	int i, built_in = -1;
	builtin_commands builtincmd[] = {
		{"exit", exit_command},
		{"env", display_envcmd},
		{"help", display_help},
		{"history", displayhistory},
		{"setenv", set_environ},
		{"unsetenv", unset_environ},
		{"cd", _cd},
		{"alias", myalias},
		{NULL, NULL}
	};

	for (i = 0; builtincmd[i].type; i++)
	{
		if (_strcmp(info->argument_vector[0], builtincmd[i].type) == 0)
		{
			info->line_number++;
			built_in = builtincmd[i].func(info);
			break;
		}
	}
	return (built_in);
}
/**
 * find_command - finds a command in PATH
 * @info: the param
 *
 * Return: void
 **/
void find_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->command_path = info->argument_vector[0];
	if (info->linenum_flag == 1)
	{
		info->line_number++;
		info->linenum_flag = 0;
	}
	for (i = 0, k = 0; info->argument[i]; i++)
		if (!_isdelimiter(info->argument[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_cmdpath(info, _getenv(info, "PATH="), info->argument_vector[0]);
	if (path)
	{
		info->command_path = path;
		fork_command(info);
	}
	else
	{
		if ((interactive_mode(info) || _getenv(info, "PATH=")
			|| info->argument_vector[0][0] == '/') &&
			is_validcmd(info, info->argument_vector[0]))
			fork_command(info);
		else if (*(info->argument) != '\n')
		{
			info->execution_status = 127;
			_error(info, "not found\n");
		}
	}
}
/**
 * fork_command - forks thread to run cmd
 * @info: param
 *
 * Return: void
 **/
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->command_path, info->argument_vector,
			get_environment(info)) == -1)
		{
			free_command(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->execution_status));
		if (WIFEXITED(info->execution_status))
		{
			info->execution_status = WEXITSTATUS(info->execution_status);
			if (info->execution_status == 126)
				_error(info, "Permission denied\n");
		}
	}
}
