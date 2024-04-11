/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:23:34 by esalmela          #+#    #+#             */
/*   Updated: 2024/02/12 17:43:44 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_strings(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i])
		words++;
	while (s[i])
	{
		if (s[i] == c)
		{
			words++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (words > 1 && s[i - 1] == c)
		words--;
	return (words);
}

static void	get_next_word(char **next_word, size_t *next_word_len, char c)
{
	size_t	i;

	*next_word += *next_word_len;
	*next_word_len = 0;
	i = 0;
	while (**next_word && **next_word == c)
		(*next_word)++;
	while ((*next_word)[i])
	{
		if ((*next_word)[i] == c)
			return ;
		(*next_word_len)++;
		i++;
	}
}

static char	**mallocfail(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*next_word;
	size_t	next_word_len;
	int		i;
	int		words;

	words = count_strings(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	i = 0;
	next_word = (char *)s;
	next_word_len = 0;
	while (i < words)
	{
		get_next_word(&next_word, &next_word_len, c);
		arr[i] = (char *)malloc(sizeof(char) * (next_word_len + 1));
		if (!arr[i])
			return (mallocfail(arr));
		ft_strlcpy(arr[i], next_word, next_word_len + 1);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
