/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:45:38 by bde-sous          #+#    #+#             */
/*   Updated: 2023/09/12 21:08:35 by ledos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp, char *cmd)
{
	char	**split;
	char	**ptr;
	char	*cmd_path;
	char	*aux;

	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	aux = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
	split = ft_split(aux, ':');
	free(aux);
	ptr = split;
	while (*split)
	{
		cmd_path = ft_strjoin(*split++, cmd);
		if (!cmd_path)
			perror(strerror(errno));
		if (!access(cmd_path, F_OK))
			break ;
		free(cmd_path);
		cmd_path = 0;
	}
	ft_freedoublepointer(ptr);
	return (cmd_path);
}

void	first_process(int fd_pipe[2], char **av, char **envp, char *path)
{
	int		pid;
	int		fd;
	char	**flags;
	int		status;

	status = 0;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		perror(strerror(errno));
	flags = ft_split(av[2], ft_checkforquotes(av[2]));
	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		close(fd_pipe[0]);
		dup2(fd, STDIN_FILENO);
		dup2(fd_pipe[1], STDOUT_FILENO);
		execve(path, flags, envp);
		close(fd_pipe[1]);
	}
	waitpid(-1, &status, WNOHANG);
	ft_freedoublepointer(flags);
	close(fd);
}

int	second_process(int fd_pipe[2], char **av, char **envp, char *path)
{
	int		pid;
	int		fd;
	char	**flags;
	int		status;

	status = 0;
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (127);
	flags = ft_split(av[3], ft_checkforquotes(av[3]));
	pid = fork();
	if (pid == -1)
		perror(strerror(errno));
	if (pid == 0)
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		execve(path, flags, envp);
		close(fd_pipe[0]);
	}
	waitpid(pid, &status, WNOHANG);
	ft_freedoublepointer(flags);
	close(fd);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_pipe[2];
	char	*path;
	char	*aux;
	int		status;
	int		i;

	i = 2;
	if (argc != 5)
		return (1);
	if (pipe(fd_pipe) == -1)
		perror(strerror(errno));
	while (i < (argc - 1))
	{
		aux = firstword(argv[i]);
		path = find_path(envp, aux);
		free(aux);
		if (!path)
			perror("command not found");
		if (i++ == 2)
			first_process(fd_pipe, argv, envp, path);
		else
			status = second_process(fd_pipe, argv, envp, path);
		free(path);
	}
	return (status);
}
