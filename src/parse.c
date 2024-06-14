/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:08:07 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/14 15:57:52 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static bool	is_cmd(t_data *data, int i)
{
	if (data->lexer_array[i].type != TOKEN_STR
		&& data->lexer_array[i].type != TOKEN_DOLAR
		&& data->lexer_array[i].type != TOKEN_DQUOTE_OPEN
		&& data->lexer_array[i].type != TOKEN_S_QUOTE)
		return (true);
	return (false);
}

static int	print_recd_error_utils(t_data *data, int i)
{
	if (is_redic(data, i) == true)
		return (-1);
	return (i);
}

bool	print_recd_error(t_data *data, int i)
{
	if (data->lexer_array[i].type == TOKEN_SPACE)
		i++;
	print_recd_error_utils(data, i);
	if (data->lexer_array[i].type == TOKEN_EOL || i == -1)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (true);
	}
	if (is_cmd(data, i) == true)
	{
		if (data->lexer_array[i].type == TOKEN_OUT_REDIRECT
			&& data->lexer_array[i - 1].type == TOKEN_REDIR_APPEND)
			printf("minishell: syntax error near unexpected token >\n");
		if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
			&& data->lexer_array[i - 1].type == TOKEN_HEREDOC)
			printf("minishell: syntax error near unexpected token <\n");
		if (data->lexer_array[i].type == TOKEN_REDIR_APPEND
			&& data->lexer_array[i - 1].type == TOKEN_REDIR_APPEND)
			printf("minishell: syntax error near unexpected token >>\n");
		if (data->lexer_array[i].type == TOKEN_HEREDOC
			&& data->lexer_array[i - 1].type == TOKEN_HEREDOC)
			printf("minishell: syntax error near unexpected token <<\n");
		return (true);
	}
	return (false);
}

bool	check_error_token(t_data *data)
{
	int	i;

	i = 0;
	while (data->lexer_array[i].type != TOKEN_EOL)
	{
		if (data->lexer_array[i].type == TOKEN_PIPE)
		{
			i++;
			data->i_pipex++;
			pipex_parse_error(data, i);
		}
		if (is_redic(data, i) == true)
		{
			i++;
			if (print_recd_error(data, i) == true)
				return (false);
		}
		if (data->lexer_array[i].type == TOKEN_ERROR)
			return (false);
		if (data->i_pipex == -1)
			return (false);
		i++;
	}
	return (true);
}

void	creating_parse(t_data *data)
{
	t_parse	*parse;
	int		i;

	data->i_pipex = 1;
	if (check_error_token(data) != true)
	{
		free(data->lexer_array);
		data->exit_status = 258;
		return ;
	}
	parse = safe_calloc(data->i_pipex + 1, sizeof(t_parse), data);
	i = -1;
	while (++i < data->i_pipex)
	{
		parse[i].cmd = NULL;
		parse[i].rec_file = NULL;
		parse[i].outfile = FALSE;
	}
	add_data_to_parse(parse, data, data->i_pipex);
	data->parse = parse;
}
