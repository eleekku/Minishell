/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:26:04 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/08 15:01:09 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	lens;
	int	i;
	int	j;

	i = 0;
	j = 0;
	lens = ft_strlen(s1);
	if (lens == 0)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[i]) && i < lens)
		i++;
	while (ft_strrchr(set, s1[lens - j - 1]) && (lens - j > 0))
		j++;
	return (ft_substr(s1, i, (lens - i - j)));
}
