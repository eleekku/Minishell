/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:03:03 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/07 17:02:56 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_space(t_token *token, t_char_iter *iter)
{
	token->type = TOKEN_SPACE;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 0;
	while (char_iter_cursor(iter) != iter->end && (char_iter_peek(iter) == ' '
			|| char_iter_peek(iter) == '\t'))
	{
		char_iter_next(iter);
		token->pos.len++;
	}
}

void	take_pipe(t_token *token, t_char_iter *iter)
{
	token->type = TOKEN_PIPE;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 1;
	char_iter_next(iter);
}

void	add_token(t_token *token, t_char_iter *iter)
{
	if (iter->start[0] == '<' && iter->d_flag % 2 == 0)
		take_redir_in(token, iter);
	else if (iter->start[0] == '>' && iter->d_flag % 2 == 0)
		take_redir_out(token, iter);
	else if (iter->start[0] == '\'' && iter->d_flag % 2 == 0)
		take_s_quote(token, iter);
	else if ((iter->start[0] == ' ' || iter->start[0] == '\t')
		&& iter->d_flag % 2 == 0)
		take_space(token, iter);
	else if (iter->start[0] == '"')
		take_d_quote(token, iter);
	else if (iter->start[0] == 31 && iter->d_flag % 2 == 0)
		take_exp(token, iter);
	else if (iter->start[0] == '$' && (iter->start[1] == '\0'
			|| iter->start[1] == '?'
			|| iter->start[1] == ' '
			|| iter->start[1] == '$'
			|| iter->start[1] == '=' || ft_isdigit(iter->start[1])))
		take_just_dollar(token, iter);
	else if (iter->start[0] == '$' && iter->start[1] != '?' && iter->start[1])
		take_dollar(token, iter);
	else if (iter->start[0] == '|' && iter->d_flag % 2 == 0)
		take_pipe(token, iter);
	else
		take_string(token, iter);
}

void	take_error(t_token *token, t_char_iter *iter)
{
	token->type = TOKEN_ERROR;
	token->pos.start = char_iter_cursor(iter);
	printf("found unclosed quote %s\n", token->pos.start);
	token->pos.len = 0;
	while (char_iter_cursor(iter) != iter->end)
	{
		token->pos.len++;
		char_iter_next(iter);
	}
}

char	*ft_add_cmd_str(const char *src, int len)
{
	char	*new;
	size_t	i;

	new = malloc(sizeof(char) * (len + 1));
	if (!new)
	{
		return (NULL);
	}
	i = 0;
	while (src[i] && len > 0)
	{
		new[i] = src[i];
		i++;
		len--;
	}
	new[i] = '\0';
	return (new);
}
