#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

int ft_heredoc(char *escape);
int ft_process_input(int i, int fd_input, t_info *info, int fd_heredoc);
int ft_process_output(int i, int fd, t_info *info);
int ft_process_fd(t_info *info);

#endif