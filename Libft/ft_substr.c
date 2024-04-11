/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:58:44 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/08 14:27:31 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*dothemalloc(unsigned int slen, unsigned int start, size_t len)
{
	char	*str;

	if (len > (slen - start))
		str = (char *)malloc(sizeof(char) * ((slen - start) + 1));
	else
		str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	return (str);
}

static char	*createres(char const *s, unsigned int start, size_t len, char *str)
{
	int	slen;
	int	i;

	slen = ft_strlen(s);
	i = 0;
	while (s[i])
	{
		if (s[i] == s[start])
		{
			if (len > (slen - start))
			{
				ft_memcpy(str, s + i, (slen - start));
				str[slen - start] = '\0';
			}
			else
			{
				ft_memcpy(str, s + i, len);
				str[len] = '\0';
			}
			return (str);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	slen;

	slen = ft_strlen(s);
	if (slen <= start)
		return (ft_strdup(""));
	str = dothemalloc(slen, start, len);
	if (str == NULL)
		return (NULL);
	return (createres(s, start, len, str));
}
