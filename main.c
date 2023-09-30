/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 14:31:01 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/30 14:32:44 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"
#include <stdlib.h>

int	checkclosedquotes(char *str)
{
	int	doubleq;
	int	singleq;
	int	i;

	i = -1;
	doubleq = 0;
	singleq = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			doubleq++;
		if (str[i] == '\'')
			singleq++;
	}
	return ((doubleq % 2 == 0) && (singleq % 2 == 0));
}

int	parser(t_token *tokens, t_info *info)
{
	int	i;

	i = -1;
	if (!checkclosedquotes(info->str))
		return (0);
	while (++i < tokens[0].total) 
	{
		if (!ft_strcmp(tokens[i].t, "&&"))
			return (0);
		if (!ft_strcmp(tokens[i].t, "||"))
			return (0);
		if (!ft_strcmp(tokens[i].t, "<<") && tokens[0].total == 1)
			return (0);
		if (!ft_strcmp(tokens[tokens[0].total - 1].t, "|"))
			return (0);
		if (!ft_strcmp(tokens[i].t, "<") && tokens[0].total == 1)
			return (0);
		if (!ft_strcmp(tokens[i].t, ">") && tokens[0].total == 1)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	(void) argc;
	(void) argv;
	info.tenv = ft_convert_envp(envp);
	while (1)
	{
		info.envp = list_to_doublepointer(info.tenv);
		signals();
		info.str = readline("\033[1;95msusanashell # \033[0m");
		add_history(info.str);
		info.exit_code = 0 ;
		if (ft_strlen(info.str) > 0)
		{
			info.tokens = dividetokens(info.str, info.tenv);
			if (!info.tokens)
				continue ;
			changetokentypes(info.tokens);
			if (parser(info.tokens, &info) == 0)
			{
				printf("Muito bom input!\n");
				continue ;
			}
			info.ordem = -1;
			info.fds[0] = 0;
			info.fds[1] = 1;
			info.flag_stop = 0;
			ft_main_exec(&info);
			ft_freetokens(info.tokens);
		}
		ft_freedoublepointer(info.envp);
		free(info.str);
	}
}
