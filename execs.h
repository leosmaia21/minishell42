#ifndef EXECS_H
# define EXECS_H

# include "minishell.h"

int	ft_envlstsize(t_envp *lst);
int	ft_count_command(t_token *tokens);
void ft_close_double_fd(int a, int b);
void ft_midle_aux(int fd_pipe[2], int temp_fd[2], t_info *info);

#endif