#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
#define MAX_CMD_LEN 256
#define MAX_ARGS 1

/**
 * display_shell_prompt - Display a simple shell prompt
 */
void display_shell_prompt(void)
{
	printf("$ "); /* Display a simple prompt */
}
/**
 * main - Entry point of the shell command line interpreter
 *
 * Return: 0 on success
 */
int main(void)
{
	char cmd[MAX_CMD_LEN];
	int exit_shell = 0;

	while (!exit_shell)
	{
		display_shell_prompt(); /* Display the prompt */
		if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL) /* Read command from stdin */
		{
			if (feof(stdin)) /* End of file condition (Ctrl+D) */
			{
				printf("\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("Error");
				exit(EXIT_FAILURE);
			}
		}

		cmd[strcspn(cmd, "\n")] = '\0'; /* Remove trailing newline character */
		execute_shell_command(custom_tokenize(cmd), &exit_shell); /* Execute the command */
	}

	return 0;
}
