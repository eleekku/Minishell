/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_doble_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:16:16 by dzurita           #+#    #+#             */
/*   Updated: 2024/04/24 16:16:19 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	char	**temp;

	if (!args || !*args)
		return ;
	temp = args;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(args);
	args = NULL;
}
