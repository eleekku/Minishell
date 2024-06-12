/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_recd_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:15:23 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/12 14:27:15 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static bool	redirect_quote_closed(t_data *data, int i_token)
{
	if (data->lexer_array[i_token].type == TOKEN_SPACE
		|| data->lexer_array[i_token].type == TOKEN_EOL)
		return (true);
	return (false);
}

static char	*redir_dolar_or_str(t_data *data, int i_token)
{
	char	*temp2;

	if (data->lexer_array[i_token].type == TOKEN_SPACE)
		i_token++;
	if (data->lexer_array[i_token].type == TOKEN_DOLAR)
		temp2 = str_redc_dolar(data, i_token);
	if (data->lexer_array[i_token].type == TOKEN_STR)
		temp2 = ft_add_cmd_str(data->lexer_array[i_token].pos.start,
				data->lexer_array[i_token].pos.len, data);
	if (data->lexer_array[i_token].type == TOKEN_DQUOTE_OPEN
		|| data->lexer_array[i_token].type == TOKEN_S_QUOTE)
	{
		temp2 = make_str_dquote(data, i_token,
				index_after_quate(data, i_token));
		i_token = index_after_quate(data, i_token) - 1;
	}
	data->i_token = i_token;
	return (temp2);
}

static char	*make_recd_str_utils(t_data *data, char *temp2, int i_token)
{
	if (data->lexer_array[i_token].type == TOKEN_DQUOTE_OPEN
		|| data->lexer_array[i_token].type == TOKEN_S_QUOTE)
	{
		if (data->lexer_array[i_token + 1].type == TOKEN_DQUOTE_CLOSED
			&& data->lexer_array[i_token].pos.len == 0)
		{
			data->is_exp = 1;
			i_token += 2;
			if (redirect_quote_closed(data, i_token) == true)
				return (safe_strdup("", data));
		}
		if (data->lexer_array[i_token].type == TOKEN_DQUOTE_OPEN
			|| data->lexer_array[i_token].type == TOKEN_S_QUOTE)
		{
			temp2 = make_str_dquote(data, i_token,
					index_after_quate(data, i_token));
			i_token = index_after_quate(data, i_token) - 1;
		}
	}
	if (data->lexer_array[i_token].type == TOKEN_DOLAR
		|| data->lexer_array[i_token].type == TOKEN_STR)
		temp2 = redir_dolar_or_str(data, i_token);
	data->i_token = i_token;
	return (temp2);
}

char	*make_recd_str(t_data *data, int i_token)
{
	char	*tem1;
	char	*temp2;
	char	*rec;

	temp2 = NULL;
	data->is_exp = 0;
	tem1 = ft_add_cmd_str(data->lexer_array[i_token].pos.start,
			data->lexer_array[i_token].pos.len, data);
	i_token++;
	if (data->lexer_array[i_token].type == TOKEN_SPACE)
		i_token++;
	temp2 = make_recd_str_utils(data, temp2, i_token);
	if (!temp2)
		safe_strdup(NULL, data);
	rec = safe_strjoin(tem1, temp2, data);
	free(tem1);
	free(temp2);
	return (rec);
}
