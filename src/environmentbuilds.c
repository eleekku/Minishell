/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmentbuilds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:10:34 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/10 16:29:28 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	unset_variable(t_data *content, char **args)
{
	int	i;

	i = 0;
	while (content->env[i] && ft_strncmp(args[1],
			content->env[i], ft_strlen(args[1])) != 0)
		i++;
	if (content->env[i])
	{
		free(content->env[i]);
		content->env[i] = safe_strdup("", content);
	}
	i = 0;
	while (content->exp[i] && ft_strncmp(args[1], content->exp[i],
			ft_strlen(args[1])) != 0)
		i++;
	if (content->exp[i])
	{
		free(content->exp[i]);
		content->exp[i] = safe_strdup("", content);
	}
	content->exit_status = 0;
}

t_bool	exit_lvl(t_data *cnt)
{
	int		i;
	int		lvl;
	char	*arg;

	i = 0;
	while (cnt->env[i] && ft_strncmp(cnt->env[i], "SHLVL", 5) != 0)
		i++;
	if (cnt->env[i])
	{
		lvl = ft_atoi((ft_strchr(cnt->env[i], '=') + 1));
		if (lvl > 1)
		{
			arg = safe_strjoin("SHLVL=", ft_itoa(lvl - 1), cnt);
			initialize_export(cnt, arg);
			free(arg);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	convert_status(int i)
{
	if (i < 0 && i >= -256)
		i = 256 + i;
	if (i > 255)
		i = i % 256;
	if (i < -256)
		i = 256 + (i % 256);
	return (i);
}

void	built_exit(char **args, t_data *cnt)
{
	int		i;
	t_bool	flag;

	flag = FALSE;
	ft_printf(1, "exit\n");
	if (!args[1])
		i = 0;
	else if ((ft_atoi(args[1])) == 0 && ft_isdigit(args[1][0]) == 0)
	{
		ft_printf(2, "minishell$: exit: %s: numeric argument required\n",
			args[1]);
		flag = TRUE;
		i = 255;
	}
	else
		i = ft_atoi(args[1]);
	if (args[1] && args[2] && flag == FALSE)
	{
		ft_printf(2, "minishell$: exit: %s too many arguments\n", args[1]);
		cnt->exit_status = 1;
		return ;
	}
	i = convert_status(i);
	cnt->exit_status = i;
	prepare_exit(cnt, i);
}

void	env(t_data *content)
{
	int	i;

	i = -1;
	while (content->env[++i])
	{
		if (content->env[i] && ft_strlen(content->env[i]) > 0)
			ft_putendl_fd(content->env[i], 1);
	}
	content->exit_status = 0;
}
