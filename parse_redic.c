/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:49:57 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/12 14:16:16 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		temp = safe_substr(data->lexer_array[i].pos.start, 0,
				data->lexer_array[i].pos.len, data);
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
			data->irec++;
		i++;
	}
}
