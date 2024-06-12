/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:03:08 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/12 14:03:33 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_dolar(t_data *data, t_parse *parse, int i_token, int i_parse)
{
	char	*str;
	int		len;

	str = NULL;
	len = data->lexer_array[i_token].pos.len;
	if (data->lexer_array[i_token].pos.start[0] == '?')
	{
		parse->cmd[data->i_str] = ft_itoa(data->exit_status);
		if (!parse->cmd[data->i_str])
		{
			ft_printf(2, "minishell$: fatal error with malloc\n");
			prepare_exit(data, 1);
		}
		return ;
	}
	else
		str = ft_add_cmd_str(data->lexer_array[i_token].pos.start, len, data);
	if (parse_dolar_envp(data, parse, str, i_token) == true)
		return ;
	free(str);
	parse[i_parse].cmd[data->i_str] = safe_strdup("", data);
}

void	parse_str(t_data *data, t_parse *parse, int i_parse)
{
	int	i;

	i = data->i_token;
	data->i_str = 0;
	while (data->lexer_array[i].type != TOKEN_EOL
		&& data->lexer_array[i].type != TOKEN_PIPE)
	{
		if (data->lexer_array[i].type == TOKEN_DOLAR)
		{
			parse_dolar(data, parse, i, i_parse);
		}
		i = parse_str_loop(data, parse, i_parse, i);
		if (is_redic(data, i) == true)
		{
			i++;
			if (data->lexer_array[i].type == TOKEN_SPACE)
				i++;
			if (data->lexer_array[i].type == TOKEN_S_QUOTE
				|| data->lexer_array[i].type == TOKEN_DQUOTE_OPEN)
				i = index_after_quate(data, i) - 1;
		}
		if (data->lexer_array[i].type == TOKEN_EOL)
			break ;
		i++;
	}
}
