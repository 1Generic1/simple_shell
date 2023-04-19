#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
 * execute_shell_command - Execute a shell command
 * @cmd: The command to execute
 */
void execute_shell_command(char *cmd)
{
	pid_t child_pid;
	int status;

	child_pid = fork(); /* Fork a child process */

	if (child_pid == 0) /* Child process */
	{
		char *args[MAX_ARGS + 1];
		args[0] = cmd;
		args[1] = NULL; /* Null-terminate the argument list */
		execve(cmd, args, NULL); /* Execute the command */
		perror("Error"); /* Print error message if execve fails */
		exit(EXIT_FAILURE);
	}
	else if (child_pid < 0) /* Forking failed */
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else /* Parent process */
	{
		wait(&status); /* Wait for the child process to finish */
	}
}

/**
 * main - Entry point of the shell command line interpreter
 *
 * Return: 0 on success
 */
int main(void)
{
	char cmd[MAX_CMD_LEN];

	while (1)
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

		execute_shell_command(cmd); /* Execute the command */
	}

	return 0;
}

