#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE_READ 1024
#define BUFFER_SIZE_WRITE 1024
#define FLUSH_BUFFER -1

#define COMMAND_NORMAL   0
#define COMMAND_OR     1
#define COMMAND_AND    2
#define COMMAND_CHAIN  3

#define TO_LOWER_CASE  1
#define TO_UNSIGNED   2

#define USE_GETLINE 0
#define USE_STRTOK  0;

#define HISTORY_FILE ".custom_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct string_node - singly linked list
 * @num: number field
 * @str: string
 * @next: point to net node
 **/
typedef struct string_node
{
	int number;
	char *text;
	struct string_node *next;
} list_t;

/*
 *struct command_info - contains pseudo-arguements to pass into a function,
 *			allowing uniform prototype for function pointer struct
 *@argument: string from getline
 *@argument_vector: array of string
 *@command_path: string with current command
 *        path of current command
 *@argument_count: argument count
 *@line_number: error count
 *@error_number: error code
 *@linenum_flag: if on count
 *file_name: program filename
 *@environment: linked list local copy
 *@command_history: history mode
 *@command_alias: alias node
 *@environment_changed: on if environ was changed
 *@execution_status: return status of ;ast executed
 *@buffer_pointer: address of pointer to cmd_buf
 *@buffer_type: CMD_type ||, &&, ;
 *@read_file: the fd from which to read line input
 *@history_count: the history line number count
 */
typedef struct passinfo
{
	char *argument;
	char **argument_vector;
	char *command_path;
	int argument_count;
	unsigned int line_number;
	int error_number;
	int linenum_flag;
	char *file_name;
	list_t *environment;
	list_t *command_history;
	list_t *command_alias;
	char **custom_environment;
	int environment_changed;
	int execution_status;
	char **buffer_pointer;
	int buffer_type;
	int read_file;
	int history_count;
} info_t;

#define COMMAND_INFO_INITIALIZER \
{ NULL, NULL, NULL, 0, 0, 0, 0, NULL, \
	NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0 }

/**
 * struct builtin - built in string
 * @type: builtin command flag
 * @func: the function
 **/
typedef struct builtin_command
{
	char *type;
	int (*func)(info_t *);
} builtin_commands;

/*toem_shloop.c*/
int custom_shell(info_t *, char **);
int identify_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/*parser.c*/
int is_validcmd(info_t *, char *);
char *duplicate_characters(char *, int, int);
char *find_cmdpath(info_t *, char *, char *);

/*toem_errors.c*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/*toem_string.c*/
int _strlen(char *);
int _strcmp(char *, char *);
char *_startwith(const char *, const char *);
char *_strcat(char *, char *);

/*string1.c*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/*exits.c*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/*tokenizer.c*/
char **strtow(char *, char *);
char **strtow2(char *, char);

/*realloc.c*/
char *set_memory(char *, char, unsigned int);
void free_alloc(char **);
void *_realloc(void *, unsigned int, unsigned int);

/*memory.c*/
int bfree(void **);

/*atoi.c*/
int interactive_mode(info_t *);
int _isdelimiter(char, char *);
int _isalphabetic(int);
int _atoi(char *);

/*errors1.c*/
int _eatoi(char *);
void _error(info_t *, char *);
int _printd(int, int);
char *convert_to_string(long int, int, int);
void remove_comlines(char *);

/*builtin.c*/
int exit_command(info_t *);
int _cd(info_t *);
int display_help(info_t *);

/*getline.c*/
ssize_t read_input(info_t *);
int getline_input(info_t *, char **, size_t *);
void sigintHandler(int);

/*getinfo.c*/
void clear_command(info_t *);
void set_command(info_t *, char **);
void free_command(info_t *, int);

/*environ.c*/
char *_getenv(info_t *, const char *);
int display_env(info_t *);
int set_environ(info_t *);
int unset_environ(info_t *);
int populate_environ(info_t *);

/*getenv.c*/
char **get_environment(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/*history.c*/
char *get_hist(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist(info_t *info, char *buf, int linecount);
int renum_hist(info_t *info);

/*lists.c*/
list_t *add_String(list_t **, const char *, int);
list_t *string_end(list_t **, const char *, int);
size_t print_string(const list_t *);
int delete_stringindex(list_t **, unsigned int);
void _freestring(list_t **);

/*lists1.c*/
size_t _stringlen(const list_t *);
char **list_strings(list_t *);
size_t print_liststrings(const list_t *);
list_t *find_nodeprefix(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/*vars.c*/
int command_chain(info_t *, char *, size_t *);
void check_command(info_t *, char *, size_t *, size_t, size_t);
int replace_commandalias(info_t *);
int replace_commandvariables(info_t *);
int replace_substring(char **, char *);

int display_history(info_t *);
int myalias(info_t *);
int unsetalias(info_t *, char *);
int setalias(info_t *, char *);
int printalias(list_t *);

#endif /*SHELL.H*/
