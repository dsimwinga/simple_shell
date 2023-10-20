#include "main.h"

/**
 *parse_input - my main function
 *@input: inputs from user
 *@args: arguments
 */
void parse_input(char *input, char **args)
{
	int i = 0;
	char *token = strtok(input, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}
