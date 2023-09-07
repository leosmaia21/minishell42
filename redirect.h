#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

int ft_input_fd(t_token *tokens, int command, int default_fd);
int ft_output_fd(t_token *tokens, int command, int default_fd);
int ft_heredoc(char *escape);

#endif