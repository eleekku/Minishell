/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:39:26 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/10 15:48:14 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	*char_find_dq(t_char_iter *self)
{
	size_t	len;

	len = 1;
	while (*(self->end - len) != '"')
	{
		len++;
	}
	return (self->end - len);
}

int	ft_realloc(t_token **token, size_t size)
{
	t_token		*new;
	size_t		i;

	new = ft_calloc(size, sizeof(t_token));
	if (!new)
		return (1);
	i = 0;
	while (i < size - 1)
	{
		new[i] = (*token)[i];
		i++;
	}
	free(*token);
	*token = new;
	return (0);
}
