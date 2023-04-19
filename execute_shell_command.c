#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_CMD_LEN 256
#define MAX_ARGS 1

char *get_path(char *cmd)
{
	char *path_env = getenv("PATH"); /* Get the PATH environment variable */
	char *path = strtok(path_env, ":"); /* Tokenize the PATH variable by ':' */
	char *full_path = NULL;
	while (path != NULL)
	{
		full_path = malloc(strlen(path) + strlen(cmd) + 2); /* Allocate memory for the full path */
		sprintf(full_path, "%s/%s", path, cmd); /* Concatenate the directory path and the command */
		if (access(full_path, X_OK) == 0) /* Check if the file is executable */
			return full_path; /* Return the full path if the file is executable */
		free(full_path); /* Free the memory if the file is not executable */
		path = strtok(NULL, ":"); /* Get the next directory in PATH */
	}
	return NULL; /* Return NULL if the command is not found in any directory listed in PATH */
}
/**
 * execute_shell_command - Execute a shell command
 * @cmd: The command to execute
 * @exit_shell: A pointer to the exit shell flag
 */
void execute_shell_command(char *cmd, int *exit_shell)
{
        char *args[MAX_ARGS + 1];
        int i = 0;
        char *path_copy = NULL; 
        extern char **environ;
        char *dir = NULL; 
        char cmd_path[MAX_CMD_LEN]; 

        /* Tokenize the command line */
        args[i] = strtok(cmd, " ");
        while (args[i] != NULL && i < MAX_ARGS)
        {
                i++;
                args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL)
        {
                return; /* Empty command */
        }
        else if (strcmp(args[0], "exit") == 0)
        {
                *exit_shell = 1; /* Set the exit shell flag */
                return;
        }
        else if (strcmp(args[0], "env") == 0)
        {
                /* Print the environment variables */
                char **env = environ;
                while (*env)
                {
                        printf("%s\n", *env);
                        env++;
                }
        }
        else
        {
                /* Check if the command exists in the PATH */
                char *path = getenv("PATH");
                if (path == NULL)
                {
                        printf("Error: PATH variable not set\n");
                        return;
                }
                path_copy = strdup(path);
                dir = strtok(path_copy, ":");
                while (dir != NULL)
                {
                        snprintf(cmd_path, MAX_CMD_LEN, "%s/%s", dir, args[0]);
                        if (access(cmd_path, X_OK) == 0)
                        {
                                /* Execute the command */
                                pid_t pid = fork();
                                if (pid == -1)
                                {
                                        perror("fork");
                                        exit(EXIT_FAILURE);
                                }
                                else if (pid == 0)
                                {
                                        execv(cmd_path, args);
                                        perror("execv");
                                        exit(EXIT_FAILURE);
                                }
                                else
                                {
                                        int status;
                                        waitpid(pid, &status, 0);
                                        if (WIFEXITED(status))
                                        {
                                                int exit_status = WEXITSTATUS(status);
                                                if (exit_status != 0)
                                                {
                                                        printf("Command '%s' returned non-zero exit status %d\n", args[0], exit_status);
                                                }
                                        }
                                        else if (WIFSIGNALED(status))
                                        {
                                                int signal_num = WTERMSIG(status);
                                                printf("Command '%s' terminated by signal %d\n", args[0], signal_num);
                                        }
                                        else if (WIFSTOPPED(status))
                                        {
                                                int signal_num = WSTOPSIG(status);
                                                printf("Command '%s' stopped by signal %d\n", args[0], signal_num);
                                        }
                                }
                                free(path_copy);
                                return;
                        }
                        dir = strtok(NULL, ":");
                }
                printf("Command not found: %s\n", args[0]);
        }
        free(path_copy);
}

