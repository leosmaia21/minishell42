/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:25:11 by bde-sous          #+#    #+#             */
/*   Updated: 2023/04/13 22:05:58 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "./libft/libft.h"

void	ft_freedoublepointer(char **dptr);
char	*firstword(char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	write_stderror(char *str, int status);
size_t	ft_strlen(const char *s);
char	*find_path(char **envp, char *cmd);
void	first_process(int fd_pipe[2], char **av, char **envp, char *path);
int		second_process(int fd_pipe[2], char **av, char **envp, char *path);
int		ft_checkforquotes(char *str);

#endif