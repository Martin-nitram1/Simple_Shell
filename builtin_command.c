#include "shell.h"

/**
 * exit_command - exit the shell
 * @info: param
 *
 * Return: exit with exit status
 **/
int exit_command(info_t *info)
{
	int exit;

	if (info->argument_vector[1])
	{
		exit = _eatoi(info->argument_vectorv[1]);
		if (exit == -1)
		{
			info->status = 2;
			_error(info, "wrong! ");
		       _eputs(info->argv[1]);
		       _eputchar('\n');
			return (1);
		}
		info->err_num = _eatoi(info->argv[1]);
		return (-2);
	}
	info->error_number = -1;
	return (-2);
}
/**
 * _cd - change current dir
 * @info: param
 *
 * Return: 0 always
 **/
int _cd(info_t *info)
{
	char *i, *direct, buffer[1024];
	int _chdir;

	i = getcwd(buffer, 1024);
	if (!i)
	{
		return (1);
	}
	if (!info->argument_vector[1])
	{
		direct = _getenv(info, "HOME=");
		if (!direct)
			_chdir = chdir((direct = _getenv(info, "PWD=")) ? direct : "/");
		else
			_chdir = chdir(direct);
	}
	else if (_strcmp(info->argument_vector[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(i);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		_chdir = chdir((direct = _getenv(info, "OLDPWD=")) ? direct : "/");
	}
	else
		_chdir = chdir(info->argument_vector[1]);
	if (_chdir == -1)
	{
		_error(info, "cant move to");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * display_help - change dir
 * @info: param
 *
 * Return: 0 always
 **/
int display_help(info_t *info)
{
	char **args;

	args = info->argument_vector;
	_puts("function not set\n");
	if (0)
		_puts(*args);
	return (0);
}
