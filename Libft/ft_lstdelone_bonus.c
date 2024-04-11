/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:02:55 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/09 18:44:14 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstdelone(t_stack *lst, void (*del)(int*))
{
	if (lst == 0 || del == 0)
		return ;
	if (lst->value != 0)
		del(&lst->value);
	free(lst);
}
