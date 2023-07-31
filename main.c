/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:53:46 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/30 22:35:01 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "minishell.h"

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
	char *path = NULL;
	char **flags;

	(void)argc;
	(void)argv;
	while (1)
	{
		signals();
		info.str = readline("\033[1;95msusanashell # \033[0m");
		add_history(info.str);
		if (ft_strlen(info.str) > 0)
		{
			info.tokens = dividetokens(info.str);
			changetokentypes(info.tokens);
			t_token *tokens = info.tokens;
			for (int i = 0; i < tokens[0].total; i++) 
			{
				printf("char *: %s ", tokens[i].t);
				printf("total: %d ", tokens[i].total);
				printf("index: %d ", tokens[i].index);
				printf("type: %s \n", get_type(tokens[i].type));
			}
			info.tenv = ft_convert_envp(envp);
            info.envp = envp;
			//ev = ft_new_var(ev,"batatinhas=teste");
			//printEnvpList(ev);
			flags = jointokens(info.tokens, 0);
			// echo(flags);
			pwd(flags);
			// exitsusana(flags);
			//path = ft_findpath(info.tenv, info.envp, flags);

            // ft_main_exec(&info);
            //ft_single_exec(flags,info.envp , path);
			//printf("%s\n", ft_find_value(ev,"PWD"));
			//free(path);
		}
		free(info.str);
	}
}
