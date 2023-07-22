#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "lexer.h"
# include "envp.h"
# include "utils.h"
# include "libft/libft.h"

void	signals(void);
void	handle_sigint(int signum);
t_envp *ft_convert_envp(char **envp);
void ft_add_node(t_envp **head, t_envp *node);
t_envp *ft_create_node(char *var, char *key);
void printEnvpList(t_envp *head);
t_envp *ft_new_var(t_envp *head, char *str);

#endif