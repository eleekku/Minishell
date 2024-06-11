/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:59:39 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/11 13:54:23 by dzurita          ###   ########.fr       */
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

char	*safe_strjoin(char const *s1, char const *s2, t_data *content)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (!str)
	{
		ft_printf(2, "minishell$: fatal error with malloc\n");
		prepare_exit(content, 1);
	}
	return (str);
}

void	*safe_calloc(size_t nitems, size_t size, t_data *content)
{
	char	*ptr;

	ptr = ft_calloc(nitems, size);
	if (!ptr)
	{
		ft_printf(2, "minishell$: fatal error with malloc\n");
		prepare_exit(content, 1);
	}
	return (ptr);
}

char	*safe_strdup(const char *src, t_data *content)
{
	char	*str;

	str = NULL;
	if (src)
		str = ft_strdup(src);
	if (!str)
	{
		ft_printf(2, "minishell$: fatal error with malloc\n");
		prepare_exit(content, 1);
	}
	return (str);
}

char	*safe_substr(char const *src, unsigned int start, size_t len,
		t_data *content)
{
	char	*str;

	str = ft_substr(src, start, len);
	if (!str)
	{
		ft_printf(2, "minishell$: fatal error with malloc\n");
		prepare_exit(content, 1);
	}
	return (str);
}
