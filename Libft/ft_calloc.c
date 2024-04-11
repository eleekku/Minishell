/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 11:55:13 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/11 14:35:13 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;

	if (nitems > 0 && SIZE_MAX / nitems < size)
		return (NULL);
	ptr = malloc(nitems * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * nitems);
	return (ptr);
}
