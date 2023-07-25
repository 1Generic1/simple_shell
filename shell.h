#ifndef SHELL_H
#define SHELL_H

char *get_path(const char *cmd);
void execute_shell_command(char **args, int *exit_shell);
char *my_getline();
char **custom_tokenize(char *cmd);
int my_setenv(const char *name, const char *value);
int my_unsetenv(const char *name);
void cd_builtin(char **args);
void execute_multiple_commands(char *cmd, int *exit_shell);

#endif /* SHELL_H */
