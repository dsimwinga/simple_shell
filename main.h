#ifndef MAIN_H
#define MAIN_H

extern char **environ; /* Declare the environment variable*/
int _putchar(char c);
void parse_input(char *input, char **args);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int betty_checks(void);
#endif
