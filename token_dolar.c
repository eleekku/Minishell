/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:01:53 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/07 17:03:04 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_exp(t_token *token, t_char_iter *iter)
{
	token->type = TOKEN_S_QUOTE;
	token->pos.start = char_iter_cursor(iter) + 1;
	token->pos.len = 0;
	char_iter_next(iter);
	while (char_iter_cursor(iter) != iter->end && char_iter_peek(iter) != 31)
	{
		char_iter_next(iter);
		token->pos.len++;
	}
	if (char_iter_cursor(iter) == iter->end || char_iter_peek(iter) == 31)
	{
		token->type = TOKEN_ERROR;
		token->pos.start--;
		token->pos.len = 1;
	}
	else
		char_iter_next(iter);
}

void	take_just_dollar(t_token *token, t_char_iter *iter)
{
	token->type = TOKEN_STR;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 1;
	char_iter_next(iter);
	if (char_iter_peek(iter) == '?')
	{
		token->type = TOKEN_DOLAR;
		token->pos.start = char_iter_cursor(iter);
		char_iter_next(iter);
	}
}

void	take_dollar(t_token *token, t_char_iter *iter)
{
	token->type = TOKEN_DOLAR;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 1;
	char_iter_next(iter);
	while (char_iter_cursor(iter) != iter->end
		&& !ft_strchr(DELIMITER, char_iter_peek(iter))
		&& char_iter_peek(iter) != '/'
		&& char_iter_peek(iter) != ':'
		&& char_iter_peek(iter) != '@'
		&& char_iter_peek(iter) != '=')
	{
		char_iter_next(iter);
		token->pos.len++;
	}
	if (char_iter_cursor(iter) == iter->end && iter->d_flag % 2 == 1)
	{
		take_error(token, iter);
		return ;
	}
}