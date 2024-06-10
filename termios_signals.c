/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:20:16 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/10 11:29:53 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tcsetreadline(t_data *msh, int n)
{
	char	*input;

	tcsetattr(STDIN_FILENO, 0, &msh->new);
	if (n == 0)
		input = readline("minishell$ ");
	else
		input = readline("> ");
	tcsetattr(STDIN_FILENO, 0, &msh->old);
	return (input);
}

void	load_termios(t_data *msh)
{
	tcgetattr(STDIN_FILENO, &msh->old);
	msh->new = msh->old;
	msh->new.c_lflag &= ~ECHOCTL;
}
