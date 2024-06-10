/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:17:30 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/10 11:27:15 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_num = SIGINT;
		close(0);
		write(1, "\n", 1);
	}
}

static void	parent_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_num = SIGINT;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	child_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_num = SIGINT;
		printf("\n");
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_num = SIGQUIT;
	}
}

void	receive_signal(int val)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (val == 0)
		sa.sa_handler = &parent_handler;
	else if (val == 1)
		sa.sa_handler = &heredoc_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
