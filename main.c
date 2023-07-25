/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:53:46 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/22 14:48:05 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
}

int	main(int argc, char **argv, char **envp)
{
	char *str;
	t_token *tokens;
	t_envp *ev;
	//t_envp *temp;
	//int		fd_pipe[2];
	char *path = NULL;
	char **flags;

	(void)argc;
	(void)argv; 
	ev = NULL;
	while (1)
	{
		signals();
		str = readline("\033[1;95m susanashell # \033[0m");
		add_history(str);
		if (ft_strlen(str) > 0)
		{
			tokens = dividetokens(str);
			changetokentypes(tokens);
			// for (int i = 0; i < tokens[0].total; i++) 
			// {
			// 	printf("char *: %s ", tokens[i].t);
			// 	printf("total: %d ", tokens[i].total);
			// 	printf("index: %d ", tokens[i].index);
			// 	printf("type: %s \n", get_type(tokens[i].type));
			// }
			ev = ft_convert_envp(envp);
			//ev = ft_new_var(ev,"batatinhas=teste");
			//printEnvpList(ev);
			flags = jointokens(tokens);
			path = ft_findpath(ev, envp, flags);
			if (path)
				ft_single_exec(flags,envp , path);
			//printf("%s\n", ft_find_value(ev,"PWD"));
			free(path);
		}
		free(str);
	}
}
