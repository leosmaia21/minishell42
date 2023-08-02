/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:16:47 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/29 17:17:04 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>

typedef struct s_info{
    char            *str;
    t_envp 			*tenv;
    char            **envp;
    t_token         *tokens;
    int             exit_code;
}	t_info;

void	signals(void);
void	handle_sigint(int signum);
t_envp	*ft_convert_envp(char **envp);
void 	ft_add_node(t_envp **head, t_envp *node);
t_envp 	*ft_create_node(char *var, char *key);
void	printEnvpList(t_envp *head);
t_envp 	*ft_new_var(t_envp *head, char *str);
char 	*ft_find_value(t_envp *head, char *key);
char 	*ft_findpath(t_envp *head, char **envp, char **flags);
void	ft_single_exec(char **flags, char **envp, char *path);
void	ft_freedoublepointer(char **dptr);
void 	ft_main_exec(t_info *info);
char **ft_duplicate_envp(char **envp);
int ft_check_builtin(char **flags, char **envp);

#endif
