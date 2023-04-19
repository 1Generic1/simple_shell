#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 256

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
    printf("$ "); // Display a simple prompt
}

/**
 * is_exit_command - Checks if the entered command is "exit"
 * @command: The entered command
 * Return: true if the command is "exit", false otherwise
 */
bool is_exit_command(char *command)
{
    return strcmp(command, "exit") == 0;
}

/**
 * is_env_command - Checks if the entered command is "env"
 * @command: The entered command
 * Return: true if the command is "env", false otherwise
 */
bool is_env_command(char *command)
{
    return strcmp(command, "env") == 0;
}

/**
 * execute_command - Executes the entered command
 * @command: The entered command
 */
void execute_command(char *command)
{
    pid_t pid = fork(); // Fork a child process

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Child process
        execlp(command, command, NULL); // Execute the command in the child process
        perror("exec");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        int status;
        wait(&status); // Wait for the child process to finish
    }
}

/**
 * main - Entry point for the shell
 * Return: 0 on success
 */
int main(void)
{
    char input[MAX_INPUT_LENGTH];

    while (true)
    {
        display_prompt(); // Display the prompt

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
        {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline

        if (strlen(input) == 0)
        {
            // Empty input, display prompt again
            continue;
        }

        if (is_exit_command(input))
        {
            // Exit command entered, exit the shell
            break;
        }

        if (is_env_command(input))
        {
            // Env command entered, print the current environment
            system("env");
            continue;
        }

        execute_command(input); // Execute the entered command
    }

    return 0;
}

