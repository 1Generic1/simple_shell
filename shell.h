#ifndef SHELL_H
#define SHELL_H

char *get_path(char *cmd);
void execute_shell_command(char *cmd, int *exit_shell);
char *my_getline();
#endif /* SHELL_H */
