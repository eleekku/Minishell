/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:29:34 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/10 16:35:54 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char *args, int *flag)
{
	int	i;

	i = 0;
	if (args[i] && (args[i] == '-'))
	{
		i++;
		if (args[i] == 'n')
		{
			while (args[i] == 'n')
				i++;
			if (!args[i])
			{
				*flag = 1;
				return (1);
			}
		}
	}
	return (0);
}

void	echo(char **args, t_data *content)
{
	int	i;
	int	flag;
	int	check;

	i = 0;
	flag = 0;
	check = 0;
	while (args[++i])
	{
		if (check_flag(args[i], &flag) == 0)
		{
			if (check != 0)
				ft_putchar_fd(' ', 1);
			ft_putstr_fd(args[i], 1);
			check = 1;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
	content->exit_status = 0;
}
