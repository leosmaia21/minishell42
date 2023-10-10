/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-sous <bde-sous@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:54:24 by bde-sous          #+#    #+#             */
/*   Updated: 2023/10/10 18:59:07 by bde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_sigint(int signum)
{
	struct termios	termios_save;
	struct termios	termios_new;

	(void) signum;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	if (tcgetattr(0, &termios_save) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_new) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	handle_heredoc(int signum)
{
	(void) signum;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	exit(1);
}
