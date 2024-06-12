/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:43:08 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/11 10:14:19 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	**copy_to_struct(char **table, char **new, t_data *content)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (new[i])
		i++;
	table = safe_calloc(i + 1, sizeof(char *), content);
	while (++j < i)
		table[j] = safe_strdup(new[j], content);
	free_array(new);
	return (table);
}

void	build_export(t_data *content)
{
	int	i;

	i = 0;
	while (content->env[i])
		i++;
	content->exp = safe_calloc(i + 1, sizeof(char *), content);
	i = 0;
	while (content->env[i])
	{
		content->exp[i] = ft_strdup(content->env[i]);
		if (!content->exp[i])
		{
			ft_printf(2, "minishell$: fatal error with malloc\n");
			prepare_exit(content, 1);
		}
		i++;
	}
	content->exp[i] = NULL;
}

void	print_export(t_data *content)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (content->exp[i])
	{
		if (!ft_strchr(content->exp[i], '=') && ft_strlen(content->exp[i]) > 0)
			ft_printf(1, "declare -x %s\n", content->exp[i]);
		else if (ft_strlen(content->exp[i]) > 0)
		{
			while (content->exp[i][j] != '=')
				j++;
			tmp = ft_substr(content->exp[i], 0, j);
			if (!tmp)
				exit(1);
			ft_printf(1, "declare -x %s=\"%s\"\n",
				tmp, ft_strchr(content->exp[i], '=') + 1);
			free(tmp);
		}
		i++;
		j = 0;
	}
	content->exit_status = 0;
}

char	**add_space(char **table, int linel, t_data *content)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while (table[i])
		i++;
	new = safe_calloc((i + 2), sizeof(char *), content);
	while (j < i)
	{
		new[j] = safe_strdup(table[j], content);
		j++;
	}
	new[j] = safe_calloc(linel + 1, sizeof(char), content);
	free_array(table);
	table = copy_to_struct(table, new, content);
	return (table);
}
