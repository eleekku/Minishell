/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:43:15 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/10 12:30:42 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

int	ft_lstsize(t_stack *lst)
{
	t_stack	*current;
	int		i;

	if (lst == NULL)
		return (0);
	current = lst;
	i = 1;
	while (current->next != NULL)
	{
		current = current->next;
		i++;
	}
	return (i);
}
