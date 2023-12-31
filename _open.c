#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @u: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char u, char *delim)
{
    while (*delim)
	if (*delim++ == u)
	return (1);
    return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@a: The character to input
 *Return: 1 if a is alphabetic, 0 otherwise
 */

int _isalpha(int a)
{
    if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
	return (1);
    else
	return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _open(char *s)
{
    int a, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (a = 0;  s[a] != '\0' && flag != 2; a++)
    {
	if (s[a] == '-')
	sign *= -1;

	if (s[a] >= '0' && s[a] <= '9')
	{
	flag = 1;
	result *= 10;
	result += (s[a] - '0');
	}
	else if (flag == 1)
	flag = 2;
    }

    if (sign == -1)
	output = -result;
    else
	output = result;

    return (output);
}

