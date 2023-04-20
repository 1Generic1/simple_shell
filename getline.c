#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

#define MAX_INPUT_LEN 1024

/**
 * my_getline - function implementation of getline
 *
 * Return: A dynamically allocated string containing the input line
 */

char *my_getline()
{
	static char buffer[MAX_INPUT_LEN];
	static int buffer_len = 0;
	static int buffer_position = 0;
	char *line = NULL;
	int line_len = 0;
	char c = buffer[buffer_position++];

	while (1)
	{
		if (buffer_position == buffer_len)
		{
			/* if buffer is empty, read data from stdin */
		buffer_len = read(STDIN_FILENO, buffer, MAX_INPUT_LEN);
		if (buffer_len == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		buffer_position = 0;
		}

		if (buffer_len == 0)
		{
			/* end of input */
			if (line_len == 0)
			{
				return (NULL);
			}
			else
			{
				break;
			}
		}
		if (c == '\n')
		{
			buffer_position--;
			break;
		}
		/* append character to line */
		if (line_len == 0)
		{
			line = malloc(1);
		}
		else
		{
			line = realloc(line, line_len + 1);
		}
		if (!line)
		{
			perror("malloc/realloc");
			exit(EXIT_FAILURE);
		}
		line[line_len++] = c;
	}
	if (line)
	{
		line = realloc(line, line_len + 1);
		if (!line)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		line[line_len] = '\0';
	}
	return (line);
}
