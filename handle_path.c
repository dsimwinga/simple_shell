#include "main.h"

/**
 *execute_command - my main function
 *@command: to be given
 *Return: 0 or 1
 */

void execute_command(char *command)
{

	char *path = getenv("PATH");
	char *token = strtok(path, ":");

	while (token != NULL)
	{
		char executable_path[1024];

		snprintf(executable_path, sizeof(executable_path), "%s/%s", token, command);
	if (access(executable_path, X_OK) == 0)
	{
		system(executable_path);
	return;
	}
	token = strtok(NULL, ":");
	}

    /* If the command is not found, print an error message*/
	printf("Command '%s' not found\n", command);
}
