/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_doble_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:16:16 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/10 17:18:47 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	free_args(char **args)
{
	char	**temp;

	if (!args || !*args)
		return ;
	temp = args;
	if (!temp)
		return ;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(args);
	args = NULL;
}
