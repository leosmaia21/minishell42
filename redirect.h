#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

int ft_input_fd(t_token *tokens);
int ft_output_fd(t_token *tokens);
int ft_heredoc(char *escape);

#endif