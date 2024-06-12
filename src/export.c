/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:12:36 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/11 13:17:08 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char	*manipulate_variable(t_data *cnt, int index, char *variable, char *arg)
{
	int	i;

	i = 0;
	free(cnt->exp[index]);
	while (cnt->env[i] && ft_strncmp(cnt->env[i], variable,
			ft_strlen(variable)) != 0)
		i++;
	if (cnt->env[i] && ft_strncmp(cnt->env[i], variable, ft_strlen(variable))
		== 0 && cnt->env[i][ft_strlen(variable)] == '=')
	{
		free(cnt->env[i]);
		free(variable);
		cnt->env[i] = safe_strdup(arg, cnt);
		return (safe_strdup(arg, cnt));
	}
	cnt->env = export(arg, cnt->env, cnt);
	free(variable);
	return (safe_strdup(arg, cnt));
}

char	**export(char *arg, char **table, t_data *content)
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	table = add_space(table, ft_strlen(arg), content);
	free(table[i]);
	table[i] = safe_strdup(arg, content);
	return (table);
}

void	initialize_export2(t_data *content, char *arg)
{
	int	i;

	if (ft_strchr(arg, '=') && (*(ft_strchr(arg, '=') + 1)))
		content->env = export(arg, content->env, content);
	i = 0;
	while (content->exp[i] && ft_strncmp(content->exp[i], arg,
			ft_strlen(arg)) != 0)
		i++;
	if (!content->exp[i])
		content->exp = export(arg, content->exp, content);
}

void	initialize_export(t_data *content, char *arg)
{
	int		len;
	int		i;
	char	*variable;

	if (ft_strchr(arg, '='))
	{
		len = ft_strlen(arg) - ft_strlen(ft_strchr(arg, '='));
		variable = ft_substr(arg, 0, len);
		if (!variable)
			prepare_exit(content, 1);
		i = 0;
		while (content->exp[i] && ft_strncmp(content->exp[i], variable, len)
			!= 0)
			i++;
		if (content->exp[i])
		{
			content->exp[i] = manipulate_variable(content, i, variable, arg);
			return ;
		}
		free (variable);
	}
	initialize_export2(content, arg);
}

void	pre_export(t_data *cnt)
{
	int	j;

	j = 0;
	if (!cnt->parse[0].cmd[1])
		print_export(cnt);
	else
	{
		while (cnt->parse[0].cmd[++j])
		{
			if (ft_isalpha(cnt->parse[0].cmd[j][0]) == 0)
			{
				ft_printf(2, "minishell$: export: `%s': not a valid intefier\n",
					cnt->parse[0].cmd[j]);
				cnt->exit_status = 1;
			}
			else
			{
				initialize_export(cnt, cnt->parse[0].cmd[j]);
				cnt->exit_status = 0;
			}
		}
	}
}
