/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:31:16 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/11 13:10:51 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

bool	is_redic(t_data *data, int i)
{
	if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
		|| data->lexer_array[i].type == TOKEN_OUT_REDIRECT
		|| data->lexer_array[i].type == TOKEN_REDIR_APPEND
		|| data->lexer_array[i].type == TOKEN_HEREDOC)
		return (true);
	return (false);
}

char	*check_dquote_str(t_data *data, int i_token)
{
	char	*temp2;
	int		len;

	len = data->lexer_array[i_token].pos.len;
	temp2 = NULL;
	if (data->lexer_array[i_token].type == TOKEN_DOLAR)
	{
		temp2 = parse_dolar_dquate(data, i_token);
		if (!temp2)
			return (NULL);
	}
	else
	{
		temp2 = ft_add_cmd_str(data->lexer_array[i_token].pos.start, len, data);
		if (!temp2)
			return (NULL);
	}
	return (temp2);
}

bool	check_token_str_dquote(t_data *data, int i_token)
{
	if (data->lexer_array[i_token].type == TOKEN_DQUOTE_OPEN
		|| data->lexer_array[i_token].type == TOKEN_STR
		|| data->lexer_array[i_token].type == TOKEN_S_QUOTE
		|| data->lexer_array[i_token].type == TOKEN_DOLAR)
		return (true);
	return (false);
}
