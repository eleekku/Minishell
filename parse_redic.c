/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:49:57 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/10 17:30:15 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		}
		else
		{
			temp2 = make_str_dquote(data, i_token,
					index_after_quate(data, i_token));
			i_token = index_after_quate(data, i_token) - 1;
		}
	}
	if (data->lexer_array[i_token].type == TOKEN_DOLAR)
		temp2 = str_redc_dolar(data, i_token);
	if (data->lexer_array[i_token].type == TOKEN_STR)
		temp2 = ft_add_cmd_str(data->lexer_array[i_token].pos.start,
				data->lexer_array[i_token].pos.len);
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
			data->lexer_array[i_token].pos.len);
	//check for null
	i_token++;
	if (data->lexer_array[i_token].type == TOKEN_SPACE)
		i_token++;
	temp2 = make_recd_str_utils(data, temp2, i_token);
	rec = ft_strjoin(tem1, temp2);
	//malloc handle
	free(tem1);
	free(temp2);
	return (rec);
}

void	parse_redic(t_data *data, t_parse *parse, int i_parse)
{
	int	i;
	int	i_rec;

	i = data->i_token;
	i_rec = 0;
	while (data->lexer_array[i].type != TOKEN_EOL
		&& data->lexer_array[i].type != TOKEN_PIPE)
	{
		if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
			|| data->lexer_array[i].type == TOKEN_OUT_REDIRECT
			|| data->lexer_array[i].type == TOKEN_REDIR_APPEND
			|| data->lexer_array[i].type == TOKEN_HEREDOC)
		{
			parse[i_parse].rec_file[i_rec] = make_recd_str(data, i);
			i_rec++;
			i = data->i_token;
		}
		i++;
	}
}

void	count_str_cmd(t_data *data, int i)
{
	char	*temp;
	int		len;

	if (data->lexer_array[i].type == TOKEN_STR
		|| data->lexer_array[i].type == TOKEN_DQUOTE_OPEN
		|| data->lexer_array[i].type == TOKEN_S_QUOTE)
		data->str++;
	if (data->lexer_array[i].type == TOKEN_DOLAR)
	{
		temp = ft_substr(data->lexer_array[i].pos.start, 0,
				data->lexer_array[i].pos.len);
		i = -1;
		data->str++;
		while (data->env[++i])
		{
			len = ft_strchr(data->env[i], '=') - data->env[i];
			if (ft_strncmp(data->env[i], temp + 1, len) == 0
				&& len + 1 == (int)ft_strlen(temp))
			{
				if (ft_strchr(data->env[i], ' '))
					data->str += ft_cont_str(data->env[i], ' ');
			}
		}
		free(temp);
	}
}

void	count_str_redic(t_data *data)
{
	int	i;

	i = data->i_token;
	data->str = 0;
	data->irec = 0;
	while (data->lexer_array[i].type != TOKEN_EOL
		&& data->lexer_array[i].type != TOKEN_PIPE)
	{
		if (data->lexer_array[i].type == TOKEN_STR
			|| data->lexer_array[i].type == TOKEN_DQUOTE_OPEN
			|| data->lexer_array[i].type == TOKEN_S_QUOTE
			|| data->lexer_array[i].type == TOKEN_DOLAR)
			count_str_cmd(data, i);
		if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
			|| data->lexer_array[i].type == TOKEN_OUT_REDIRECT
			|| data->lexer_array[i].type == TOKEN_REDIR_APPEND
			|| data->lexer_array[i].type == TOKEN_HEREDOC)
		{
			data->irec++;
			i++;
			if (data->lexer_array[i].type == TOKEN_SPACE)
				i++;
		}
		i++;
	}
}
