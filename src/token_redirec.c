/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:52:53 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/10 15:55:27 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	take_redir_heredoc(t_char_iter *iter, t_token *token)
{
	token->type = TOKEN_HEREDOC;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 2;
	char_iter_next(iter);
	char_iter_next(iter);
}

void	take_redir_in(t_token *token, t_char_iter *iter)
{
	char	peek_next;

	peek_next = *(iter->start + 1);
	if (peek_next != *iter->end)
	{
		if (peek_next == '<')
		{
			take_redir_heredoc(iter, token);
			return ;
		}
	}
	token->type = TOKEN_IN_REDIRECT;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 1;
	char_iter_next(iter);
}

void	take_redir_out(t_token *token, t_char_iter *iter)
{
	char	peek_next;

	peek_next = *(iter->start + 1);
	if (peek_next != *iter->end)
	{
		if (peek_next == '>')
		{
			take_redir_append(iter, token);
			return ;
		}
	}
	token->type = TOKEN_OUT_REDIRECT;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 1;
	char_iter_next(iter);
}

void	take_redir_append(t_char_iter *iter, t_token *token)
{
	token->type = TOKEN_REDIR_APPEND;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 2;
	char_iter_next(iter);
	char_iter_next(iter);
}
