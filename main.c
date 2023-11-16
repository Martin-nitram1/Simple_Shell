#include "shell.h"

/**
 * main - entry point
 * @ac: argument counter
 * @av: argument vector
 *
 * Return: 0 if success, 0 otherwise
 **/
int main(int argc, char **argv, char **env)
{
	info_t info = INFO_INIT;

	set_info (&info, env);
	hsh(&info, env);
	return (0);
}
