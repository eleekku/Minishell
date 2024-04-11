/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstitet_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:57:42 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/11 12:35:31 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_stack *lst, void (*f)(int *))
{
	while (lst != 0)
	{
		f(&lst->value);
		lst = lst->next;
	}
}
