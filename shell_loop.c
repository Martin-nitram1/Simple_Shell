
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
	while (1)
		{
			printf("$ ");

			if (get_input(info) == -1)
			{
				break;
			}
		}
	free_info(info, 1);
	return (0);
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
	int status;

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
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
		{
			info->status = WEXITSTATUS(status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
