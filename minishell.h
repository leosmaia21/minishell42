#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "lexer.h"
# include "utils.h"
# include "libft/libft.h"

void	signals(void);
void	handle_sigint(int signum);

#endif