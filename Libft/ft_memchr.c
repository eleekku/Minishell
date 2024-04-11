/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:21:25 by esalmela          #+#    #+#             */
/*   Updated: 2023/10/28 14:37:38 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	character;

	i = 0;
	s = (unsigned char *)str;
	character = (unsigned char)c;
	while (i < n)
	{
		if (*s == character)
		{
			return (s);
		}
		s++;
		i++;
	}
	return (NULL);
}
