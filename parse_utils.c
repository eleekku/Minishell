/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:27:51 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/10 14:32:22 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	current_itoken(t_data *data)
{
	int	i;

	i = data->i_token;
	while (data->lexer_array[i].type != TOKEN_EOL
		&& data->lexer_array[i].type != TOKEN_PIPE)
		i++;
	data->i_token = i + 1;
}

int	index_after_quate(t_data *data, int i)
{
	while (data->lexer_array[i].type != TOKEN_EOL
		&& data->lexer_array[i].type != TOKEN_PIPE
		&& is_redic(data, i) == false
		&& data->lexer_array[i].type != TOKEN_SPACE)
		i++;
	return (i);
}

int	ft_cont_str(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c && j == 0)
		{
			i++;
			j++;
		}
		if (*s == c && j != 0)
			j = 0;
		s++;
	}
	return (i);
}
