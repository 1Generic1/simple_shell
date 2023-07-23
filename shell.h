#ifndef SHELL_H
#define SHELL_H

char *get_path(const char *cmd);
void execute_shell_command(char **args, int *exit_shell);
char *my_getline();
char **custom_tokenize(char *cmd);
#endif /* SHELL_H */
