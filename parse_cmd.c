/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:41:57 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/12 14:10:31 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quate_closed(t_data *data, t_parse *parse, int i_parse, int i)
{
	i += 2;
	if (data->lexer_array[i].type == TOKEN_SPACE
		|| data->lexer_array[i].type == TOKEN_EOL)
	{
		parse[i_parse].cmd[data->i_str] = safe_strdup("", data);
	}
	return (i);
}

int	parse_quote(t_data *data, t_parse *parse, int i_parse, int i)
{
	int	i_token;

	if ((data->lexer_array[i].type == TOKEN_DQUOTE_OPEN
			|| data->lexer_array[i].type == TOKEN_S_QUOTE))
	{
		if (data->lexer_array[i + 1].type == TOKEN_DQUOTE_CLOSED
			&& data->lexer_array[i].pos.len == 0)
			i = check_quate_closed(data, parse, i_parse, i);
		else
		{
			i_token = index_after_quate(data, i);
			parse[i_parse].cmd[data->i_str] = make_str_dquote(data, i, i_token);
			i = index_after_quate(data, i) - 1;
			data->i_str++;
		}
	}
	return (i);
}

char	*make_str_dquote(t_data *data, int i_token, int i_quate)
{
	char	*temp2;
	char	*rec;

	rec = NULL;
	while (i_quate > i_token)
	{
		if (check_token_str_dquote(data, i_token) == true)
		{
			temp2 = check_dquote_str(data, i_token);
			if (!temp2)
			{
				free(rec);
				safe_strdup(NULL, data);
			}
			rec = ft_strjoingnl(rec, temp2);
			if (!rec)
			{
				free(temp2);
				safe_strdup(NULL, data);
			}
			free(temp2);
		}
		i_token++;
	}
	return (rec);
}

static void	parse_str_loop_utils(t_data *data, t_parse *parse,
		int i_parse, int i)
{
	char	*str;
	char	*temp;

	temp = make_str_dquote(data, i, index_after_quate(data, i));
	str = parse[i_parse].cmd[data->i_str];
	parse[i_parse].cmd[data->i_str] = ft_strjoingnl(str, temp);
	if (!parse[i_parse].cmd[data->i_str])
		safe_strdup(NULL, data);
	free(temp);
}

int	parse_str_loop(t_data *data, t_parse *parse, int i_parse, int i)
{
	char	*str;
	int		len;

	i = parse_quote(data, parse, i_parse, i);
	if (data->lexer_array[i].type == TOKEN_EOL)
		return (i);
	len = data->lexer_array[i].pos.len;
	str = data->lexer_array[i].pos.start;
	if (data->lexer_array[i].type == TOKEN_STR)
	{
		parse[i_parse].cmd[data->i_str] = ft_add_cmd_str(str, len, data);
		if (data->lexer_array[i + 1].type == TOKEN_DQUOTE_OPEN
			|| data->lexer_array[i + 1].type == TOKEN_S_QUOTE)
		{
			i++;
			parse_str_loop_utils(data, parse, i_parse, i);
			i = index_after_quate(data, i) - 1;
		}
		data->i_str++;
	}
	return (i);
}
