/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:32:02 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/10 10:45:03 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_stack	*ft_lstlast(t_stack *lst)
{
	t_stack	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}
