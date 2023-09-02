/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:53:46 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/09/02 18:19:01 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "libft/libft.h"
#include "minishell.h"
#include <stdlib.h>

char *get_type(t_tokentype type)
{
	switch (type)
	{
	case command: return("command");
	case flag: return("flag");
	case redirectL: return("redirectL");
	case redirectR: return("redirectR");
	case dredirectL: return("dredirectL");
	case dredirectR: return("dredirectR");
	case pipo: return("pipo");
	case text: return("text");
	case file: return("file");
	default: return(NULL);
	}
	return(NULL);
	return(NULL);
}

int	parser(t_token *tokens)
{
	int	i;

	i = -1;
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
    t_info 	info;
	// char *path = NULL;
	//char **flags;

	(void)argc;
	(void)argv;
	info.tenv = ft_convert_envp(envp);
	//info.envp = ft_duplicate_envp(envp);
	while (1)
	{
		info.envp = list_to_doublepointer(info.tenv);
		signals();
		info.str = readline("\033[1;95msusanashell # \033[0m");
		add_history(info.str);
		if (ft_strlen(info.str) > 0)
		{
			info.tokens = dividetokens(info.str, info.tenv);
 			changetokentypes(info.tokens);
			if (parser(info.tokens) == 0)
			{
				printf("Muito bom input!\n");
				continue ;
			}
			t_token *tokens = info.tokens;
			for (int i = 0; i < tokens[0].total; i++) 
			{
				printf("char *: %s ", tokens[i].t);
				printf("total: %d ", tokens[i].total);
				printf("index: %d ", tokens[i].index);
				printf("type: %s \n", get_type(tokens[i].type));
			}
			//ev = ft_new_var(ev,"batatinhas=teste");
			//flags = jointokens(info.tokens, 0);
			// ft_exec_builtin(flags, &info, 0);
			// echo(flags);
			//cd(flags, info.tenv);m
			// env(flags, info.tenv);
			//printf("boas");
			//pwd(flags);
			// printEnvpList(info.tenv);
			// printf("\n\n");
			// unset(flags, info.tenv);
			// exportsusana(flags, info.tenv);
			// printEnvpList(info.tenv);
			//exitsusana(flags);
			//path = ft_findpath(info.tenv, info.envp, flags);

            ft_main_exec(&info);
            // ft_single_exec(flags, info.envp , path);
			//printf("%s\n", ft_find_value(ev,"PWD"));
			//free(path);
			ft_freetokens(info.tokens);
		}
		ft_freedoublepointer(info.envp);
		free(info.str);
	}
}
