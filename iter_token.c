/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:35:59 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/10 15:47:45 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_char_iter	char_iter_constructor(char *start, size_t len)
{
	t_char_iter	iter;

	iter.start = start;
	iter.end = start + len;
	return (iter);
}

char	*char_iter_cursor(t_char_iter *self)
{
	return (self->start);
}

char	char_iter_peek(t_char_iter *self)
{
	return (*self->start);
}

char	char_iter_peek_next(t_char_iter *self)
{
	return (*(self->start + 1));
}

char	char_iter_next(t_char_iter *self)
{
	char	next;

	next = *self->start + 1;
	self->start++;
	return (next);
}
