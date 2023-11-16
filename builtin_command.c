#include "shell.h"

/**
 * _myexit - exit the shell
 * @info: param
 *
 * Return: exit with exit status
 **/
int _myexit(info_t *info)
{
	int exit;

	if (info->argv[1])
	{
		exit = _erratoi(info->argv[1]);
		if (exit == -1)
		{
			info->status = 2;
			print_error(info, "wrong! ");
		       _eputs(info->argv[1]);
		       _eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
				return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * _mycd - change current dir
 * @info: param
 *
 * Return: 0 always
 **/
int _mycd(info_t *info)
{
	char *i, *direct, buffer[1024];
	int _chdir;

	i = getcwd(buffer, sizeof(buffer));
	if (!i)
	{
		perror("getcwd");
		return (1);
	}
	if (!info->argv[1])
	{
		direct = _getenv(info, "HOME=");
		if (!direct)
			_chdir = chdir((direct = _getenv(info, "PWD=")) ? direct : "/");
		else
			_chdir = chdir(direct);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(i);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		_chdir = chdir((direct = _getenv(info, "OLDPWD=")) ? direct : "/");
	}
	else
		_chdir = chdir(info->argv[1]);
	if (_chdir == -1)
	{
		perror("chdir");
		print_error(info, "cant move to");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
	}
	return (0);
}
/**
 * _myhelp - change dir
 * @info: param
 *
 * Return: 0 always
 **/
int _myhelp(info_t *info)
{
	char **args;

	args = info->argv;
	_puts("function not set\n");
	if (0)
		_puts(*args);
	return (0);
}
