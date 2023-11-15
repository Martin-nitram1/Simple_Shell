# The Gates of Shell

![The Gates of SHell]https://s3.amazonaws.com/intranet-projects-files/holbertonschool-low_level_programming/235/shell.jpeg

This is a simple project written in C that allows execution of simple commands such as cd, ls, echo, pwd etc.
This project creates a simple shell program that can execute various Unix-like commands. 
It provides a command-line interface where users can enter commands, it execute them and display the output.

## Main Features

- Execution of Command
- Parsing of commands, arguments, and options
- Built-in commands e.g exit
- Input and output redirection
- Commands piping

### Compilation

To compile the simple shell, run the following command:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
Then run the executables through the following command:
./hsh

## Supported Commands

1. cd - change directory
2. ls - list directory contents
3. pwd - print working directory
4. echo - print text to the console
5. mkdir - create a new directory
6. rmdir - remove a directory
7. rm - remove a file
8. cp - copy a file
9. mv - move a file
10. chmod - change file permissions
11. exit - exit the shell

## Examples

```bash
$ ./hsh
hsh > ls
README.md shell.c shell.h
hsh > echo Hello, world!
Hello, world!
hsh > cd /path/to/directory
hsh > exit
$
```

## Limitations

- Limited support for complex shell features and advanced commands
- No support for environment variables or expansions
- Limited error handling

## Contributions

Contributions to improve and extend the functionality of this simple shell are welcome. 
Please submit pull requests or report issues if you find any bugs or want to add new features.


## AUTHORS

This project has been put together by Martin Omondi [info.martinomondi@gmail.com]
