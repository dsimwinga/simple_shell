#include "main.h"


int main(int argc, char *argv[])
{
     	char *command = argv[1];
	char *input;
    	size_t bufsize = 32;
    	int characters;
    	char *args[32];
    	pid_t pid;

    input = (char *)malloc(bufsize * sizeof(char));
    if (input == NULL)
    {
	perror("malloc error");
	exit(EXIT_FAILURE);
    }

	while (1)
	{
		printf("$ ");
		characters = getline(&input, &bufsize, stdin);
		if (characters == EOF)
			{
				printf("\n");
				free(input);
				exit(EXIT_SUCCESS);
			}

	input[characters - 1] = '\0'; /*remove newline char*/

	pid = fork();

	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
		{
			args[0] = input;
			args[1] = NULL;
			execve(input, args, environ); /* Pass environ as the third argument*/
			perror("execve error");
			exit(EXIT_FAILURE);
		}
	else
	{
		wait(NULL);
	}
	}

	free(input);
	return (0);

	 if (argc < 2)
 		{
 			printf("Usage: %s <command>\n", argv[0]);
			return (1);
 		}
	execute_command(command);
 	return (0);

}

