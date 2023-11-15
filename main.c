#include "shell.h"

/**
 * main - entry point
 * @ac: argument counter
 * @av: argument vector
 *
 * Return: 0 if success, 0 otherwise
 **/
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};
	int fds = 2;

	fds = fds + 3;

	if (ac == 2)
	{
		fds = open(av[1], O_RDONLY);
		if (fds == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs("; 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fds;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
