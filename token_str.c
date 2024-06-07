/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:59:00 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/07 17:00:36 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_s_quote(t_token *token, t_char_iter *iter)
{
	token->type = TOKEN_S_QUOTE;
	token->pos.start = char_iter_cursor(iter) + 1;
	token->pos.len = 0;
	char_iter_next(iter);
	while (char_iter_cursor(iter) != iter->end && char_iter_peek(iter) != '\'')
	{
		token->pos.len++;
		char_iter_next(iter);
	}
	if (char_iter_cursor(iter) == iter->end)
	{
		token->type = TOKEN_ERROR;
		token->pos.start--;
		token->pos.len = 1;
		take_error(token, iter);
		return ;
	}
	else
		char_iter_next(iter);
}

void	take_string(t_token *token, t_char_iter *iter)
{
	token->type = TOKEN_STR;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 0;
	if (iter->d_flag % 2 == 0)
	{
		while (char_iter_cursor(iter) != iter->end
			&& !ft_strchr(DELIMITER, char_iter_peek(iter)))
		{
			token->pos.len++;
			char_iter_next(iter);
		}
	}
	else
	{
		while (char_iter_cursor(iter) != iter->end
			&& char_iter_peek(iter) != '"' && char_iter_peek(iter) != '$')
		{
			token->pos.len++;
			char_iter_next(iter);
		}
		if (char_iter_cursor(iter) == iter->end)
			take_error(token, iter);
	}
}
void	take_d_quote(t_token *token, t_char_iter *iter)
{
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 0;
	if (iter->d_flag % 2 == 0)
	{
		iter->d_flag += 1;
		token->type = TOKEN_DQUOTE_OPEN;
		token->pos.start++;
		char_iter_next(iter);
		while (char_iter_cursor(iter) != iter->end
			&& char_iter_peek(iter) != '"')
		{
			if (char_iter_peek(iter) == '$' && char_iter_peek_next(iter) != ' '
				&& char_iter_peek_next(iter) != '"')
				break ;
			token->pos.len++;
			char_iter_next(iter);
		}
		if (char_iter_cursor(iter) == iter->end)
			take_error(token, iter);
		return ;
	}
	token->type = TOKEN_DQUOTE_CLOSED;
	char_iter_next(iter);
	iter->d_flag += 1;
}
