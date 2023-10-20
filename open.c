#include "shell.h"

/**
 * is_interactive - returns 1 if the shell is in interactive mode, 0 otherwise
 * @info: a struct containing information
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @u: the character to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char u, char *delim)
{
	while (*delim)
	{
		if (*delim == u)
		{
			return (1);
		}
		delim++;
	}
	return (0);
}

/**
 * is_alpha - checks for an alphabetic character
 * @u: the character to check
 * Return: 1 if u is alphabetic, 0 otherwise
 */
int is_alpha(int u)
{
	return ((u >= 'a' && u <= 'z')) || ((u >= 'A' && u <= 'Z')) ? 1 : (0);
}

/**
 * string_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in the string, the converted number otherwise
 */
int string_to_int(char *s)
{
	int i = 0;
	int sign = 1;
	int output = 0;
	unsigned int result = 0;
	int flag = 0;

	while (s[i] != '\0' && flag != 2)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}

		i++;
	}

	output = (sign == -1) ? -result : result;
	return (output);
}

