/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:59:39 by esalmela          #+#    #+#             */
/*   Updated: 2024/04/29 14:59:43 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_exit(t_data *content, int status)
{
	if (content->env)
		free_args(content->env);
	if (content->exp)
		free_args(content->exp);
	free_struct_parse(content);
	exit(status);
}

char	*safe_strjoin(char const *s1, char const *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (!str)
	{
		// call some error function
		exit(1);
	}
	return (str);
}

void	*safe_calloc(size_t nitems, size_t size)
{
	char	*ptr;

	ptr = ft_calloc(nitems, size);
	if (!ptr)
	{
		// call some error function
		exit (255);
	}
	return (ptr);
}

char	*safe_strdup(const char *src)
{
	char *str;

	str = ft_strdup(src);
	if (!str)
	{
		// call some error function
		exit (255);
	}
	return (str);
}

