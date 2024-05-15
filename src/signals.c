/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:05:11 by tsurma            #+#    #+#             */
/*   Updated: 2024/05/15 16:44:07 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executing.h"

/*
Executes when the ctrl+c signal is send.
writes a new line and reinitialises it to display the prompt*/
void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = sig;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		write(1, "\n", 2);
		rl_on_new_line();
	}
}

void	signal_handler_clean(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	return ;
}

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = sig;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
	if (sig == SIGQUIT)
	{
		return ;
	}
}

void	setsig(void)
{
	signal(SIGINT, signal_handler_clean);
	signal(SIGQUIT, sigint_handler);
}
