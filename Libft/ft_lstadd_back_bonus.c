/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:41:16 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/11 13:03:33 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*current;

	if (lst && *lst)
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else if (lst)
		*lst = new;
}
