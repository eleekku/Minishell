/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:52:37 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/10 10:46:59 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_stack	*ft_lstnew(int content, int index)
{
	t_stack	*link;

	link = (t_stack *)malloc(sizeof(t_stack));
	if (!link)
		return (NULL);
	link->value = content;
	link->index = index;
	link->seque = 0;
	link->next = NULL;
	return (link);
}
