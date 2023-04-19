#ifndef SHELL_H
#define SHELL_H

void execute_shell_command(char *cmd, int *exit_shell);
char *get_path(char *cmd);

#endif /* SHELL_H */
