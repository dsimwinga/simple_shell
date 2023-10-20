#include "shell.h"

/**
 * _eputs - Prints an input string to standard error (stderr).
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
    int a = 0;

    if (!str)
	    return;
	while (str[a] != '\0')
    {
	_eputchar(str[a]);
	a++;
    }
}

/**
 * _eputchar - Writes the character c to standard error (stderr).
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
    static int a;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
    {
	write(2, buf, a);
	a = 0;
    }
    if (c != BUF_FLUSH)
	buf[a++] = c;
    return (1);
}

/**
 * _putfd - Writes the character c to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
    static int a;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
    {
	write(fd, buf, a);
	a = 0;
    }
    if (c != BUF_FLUSH)
	buf[a++] = c;
    return (1);
}

/**
 * _putsfd - Prints an input string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
    int a = 0;

    if (!str)
	return (0);
    while (*str)
    {
	a += _putfd(*str++, fd);
    }
    return (a);
}

