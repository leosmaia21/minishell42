/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:16:47 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/09/28 22:51:51 by ledos-sa         ###   ########.fr       */
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
# include <errno.h>
# include <assert.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef enum s_token_type{
	command,
	flag,
	redirectL,
	dredirectL,
	redirectR,
	dredirectR,
	pipo,
	text,
	file
}	t_tokentype;

typedef struct s_envp{
	char			*var;
	char			*key;
	int				equal;
	struct s_envp	*next;
}	t_envp;

typedef struct s_token{
	char			*t;
	t_tokentype		type;
	int				total;
	int				index;
	int				end;
	int				pipe;
	int				expandenv;
}	t_token;

typedef struct s_info{
    char            *str;
    t_envp 			*tenv;
    char            **envp;
    t_token         *tokens;
    int             exit_code;
	int				ordem;
	int				fds[2];
	int				flag_stop;
}	t_info;

# include "envp.h"
# include "execs.h"
# include "builtins.h"
# include "utils.h"
# include "free.h"
# include "redirect.h"
# include "libft/libft.h"

void	signals(void);
void	handle_sigint(int signum);
t_envp	*ft_convert_envp(char **envp);
void	ft_add_node(t_envp **head, t_envp *node);
int		ft_change_var(t_envp *head, char *key, char *var, char *str);
t_envp	*ft_create_node(char *var, char *key);
void	printEnvpList(t_envp *head);
t_envp	*ft_new_var(t_envp *head, char *str);
char 	*ft_find_value(t_envp *head, char *key);
char 	*ft_findpath(t_envp *head, char **flags);
void	ft_single_exec(char **flags, t_info *info, char *path);
void	ft_freedoublepointer(char **dptr);
void 	ft_main_exec(t_info *info);
char 	**ft_duplicate_envp(char **envp);
void	removenode(t_envp **head, char *key);
t_envp	*tnode(t_envp *cabeca, char *key);
void	ft_exec_builtin(char **flags, t_info *info, int flag);
void 	ft_exec_pipes(t_info *info, int *input_fd, int *fd, int i);
int		ft_is_builtin(char **flags);
void	first_process(int fd_pipe[2], char **flags, t_info *info, char *path);
void	second_process(int fd_pipe[2], char **flags, t_info *info, char *path);
char	**list_to_doublepointer(t_envp *head);
void	midle_process(int	fd_pipe[2], char	**flags, t_info *info,char	*path);

#endif
