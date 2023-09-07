/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:51:31 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/07 17:20:40 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

int ft_get_id_pipe(t_token *tokens, int idx)
{
    int i;
    i = -1;
	while (idx >= 0)
	{
		while (tokens[++i].type != command)
			continue ;
		if (tokens[i].type == command)
			idx--;
	}
    return(i);
}

int ft_input_fd(t_token *tokens, int command, int default_fd)
{
    int fd;
    int i;

	i = ft_get_id_pipe(tokens, command) - 1;
    fd = default_fd;
    while ((++i < tokens[0].total) && (tokens[i].type != pipo))
	{
        if ((tokens[i].type == redirectL) || (tokens[i].type == dredirectL))
        {
            if (fd != default_fd)
                close(fd);
            if (tokens[i].type == dredirectL)
            {
                fd = ft_heredoc(tokens[i + 1].t);
            }
            else
            {
                if (!access(tokens[i + 1].t, F_OK))
                    fd = open(tokens[i + 1].t, O_RDONLY);
                else
                    perror(tokens[i + 1].t);
            }
            i++;
        }
    }
    return(fd);
}

int ft_output_fd(t_token *tokens, int command, int default_fd)
{
    int fd;
    int i;

	i = ft_get_id_pipe(tokens, command);
    fd = default_fd;
	// while (((tokens[i].type != redirectR) && (tokens[i].type != dredirectR)) && (i < tokens[0].total - 1))
    //     i++;
    // if (i == tokens[0].total - 1)
    //     return(fd);
    while ((++i < tokens[0].total) && (tokens[i].type != pipo)) 
    {
        if ((tokens[i].type == redirectR) || (tokens[i].type == dredirectR))
        {
            if (fd != default_fd)
                close(fd);
            if (tokens[i].type == redirectR)
                fd = open(tokens[i + 1].t, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else
                fd = open(tokens[i + 1].t, O_CREAT | O_RDWR | O_APPEND, 0666);
            if (fd == -1)
                perror(tokens[i + 1].t);
            i = i + 2;
        }
    }
    //printf("estou aqui\n");
    return(fd);
}

int ft_heredoc(char *escape) {
    int fd[2];
    int pid;
    int fd_return;
    char *str;

    if (pipe(fd) == -1) 
    {
        perror("pipe");
        return -1;
    }
    pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        return -1;
    }
    if (pid == 0) 
    {
        close(fd[0]);
        while (1) 
        {
            str = readline("> ");
            if (ft_strcmp(str, escape) == 0) 
            {
                free(str);
                break;
            }
            ft_putstr_fd(str, fd[1]);
            ft_putstr_fd("\n", fd[1]);
            free(str);
        }
        close(fd[1]);
        exit(0); 
    } 
    else 
    {
        close(fd[1]);
        waitpid(pid, NULL, 0);
        fd_return = dup(fd[0]);
        close(fd[0]);
    }

    return fd_return;
}