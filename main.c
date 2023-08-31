/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:53:46 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/08/31 18:28:46 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
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

int	main(int argc, char **argv, char **envp)
{
    t_info info;
	// char *path = NULL;
	char **flags;

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
			t_token *tokens = info.tokens;
			for (int i = 0; i < tokens[0].total; i++) 
			{
				printf("char *: %s ", tokens[i].t);
				printf("total: %d ", tokens[i].total);
				printf("index: %d ", tokens[i].index);
				printf("type: %s \n", get_type(tokens[i].type));
			}
			//ev = ft_new_var(ev,"batatinhas=teste");
			flags = jointokens(info.tokens, 0);
			// ft_exec_builtin(flags, &info, 0);
			// echo(flags);
			// cd(flags, info.tenv);
			// env(flags, info.tenv);
			// printf("boas");
			// pwd(flags);
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
			// ft_freetokens(info.tokens);
		}
		ft_freedoublepointer(info.envp);
		free(info.str);
	}
}
