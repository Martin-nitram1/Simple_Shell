#include "shell.h"

/**
 * hsh -  main loop for the shell
 * @info: param
 * @av: the argument vector
 *
 * Return: 0 if success 1 if fail and err no
 **/
int hsh(info_t *info, char **av)
{
	ssize_t rs = 0;
	int builtin_r = 0;

	while (rs != -1 && builtin_r != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		rs = get_input(info);
		if (rs != -1)
		{
			set_info(info, av);
			builtin_r = find_builtin(info);
			if (builtin_r == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_r == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_r);
}
/**
 * find_builtin - finds builtin command
 * @info: param
 *
 * Return: -1 if not found, 0 if executed success,
 * 1 if found but not executed, -2 if signal exits
 **/
int find_builtin(info_t *info)
{
	int i, built_in = -1;
	builtin_table builtintbl[] = {
		{"exits", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
	{
		info->line_count++;
		built_in = builtintbl[i].func(info);
		break;
	}
	return (built_in);
}
/**
 * find_cmd - finds a command in PATH
 * @info: the param
 *
 * Return: void
 **/
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
/**
 * fork_cmd - forks thread to run cmd
 * @info: param
 *
 * Return: void
 **/
void fork_cmd(info_t *info)
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
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
