/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:15:59 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/10 14:24:28 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_stack *lst)
{
	t_stack	*current;

	if (lst)
	{
		while (lst)
		{
			current = (lst)->next;
			free(lst);
			(lst) = current;
		}
	}
}
