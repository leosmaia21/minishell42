/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:53:46 by ledos-sa          #+#    #+#             */
/*   Updated: 2023/07/16 14:28:22 by ledos-sa         ###   ########.fr       */
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

	(void)argc;
	(void)argv; 
	(void)envp;
	while(1)
	{
		signals();
		// str = readfromstdin();
		str = readline("susanashell # ");
		add_history(str);
		if (ft_strlen(str) > 0)
		{
			tokens = dividetokens(str);
			changetokentypes(tokens);
			for (int i = 0; i < tokens[0].total; i++) 
			{
				printf("char *: %s ", tokens[i].t);
				printf("total: %d ", tokens[i].total);
				printf("index: %d ", tokens[i].index);
				printf("type: %s \n", get_type(tokens[i].type));
			}
		}
	}
}
