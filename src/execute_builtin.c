/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:30:08 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/10 17:03:48 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "inc/minishell.h"

void	run_builtin_child(char **args, t_data *cnt)
{
	if (ft_strncmp(args[0], "echo", 4) == 0)
	{
		echo(args, cnt);
		exit (0);
	}
	else if (ft_strncmp(args[0], "pwd", 3) == 0 && ft_strlen(args[0]) == 3)
	{
		print_pwd(cnt);
		exit (0);
	}
	else if (ft_strncmp(args[0], "env", 3) == 0 && ft_strlen(args[0]) == 3)
	{
		env(cnt);
		exit (0);
	}
	else if (ft_strncmp(args[0], "exit", 4) == 0 && ft_strlen(args[0]) == 4)
		built_exit(args, cnt);
	else if (ft_strncmp(args[0], "export", 4) == 0 && ft_strlen(args[0]) == 6)
		print_export(cnt);
	exit (0);
}

void	run_builtin2(t_data *cnt)
{
	if (ft_strncmp(cnt->parse[0].cmd[0], "echo", 4) == 0)
		echo(cnt->parse[0].cmd, cnt);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "pwd", 3) == 0
		&& ft_strlen(cnt->parse[0].cmd[0]) == 3)
		print_pwd(cnt);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "env", 3) == 0
		&& ft_strlen(cnt->parse[0].cmd[0]) == 3)
		env(cnt);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "export", 6) == 0
		&& ft_strlen(cnt->parse[0].cmd[0]) == 6)
		pre_export(cnt);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "cd", 2) == 0
		&& ft_strlen(cnt->parse[0].cmd[0]) == 2)
		change_directory(cnt->parse[0].cmd[1], cnt);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "exit", 4) == 0
		&& ft_strlen(cnt->parse[0].cmd[0]) == 4)
		built_exit(cnt->parse[0].cmd, cnt);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "unset", 5) == 0
		&& ft_strlen(cnt->parse[0].cmd[0]) == 5)
		unset_variable(cnt, cnt->parse[0].cmd);
}

void	run_builtin(t_data *cnt)
{
	if (cnt->parse[0].rec_file)
		if (redirect(cnt, 0) < 0)
			return ;
	if (!cnt->parse)
		return ;
	if (!cnt->parse[0].cmd[0])
		return ;
	run_builtin2(cnt);
}

t_bool	check_built_in(char **args)
{
	if (!args)
		return (FALSE);
	if (!args[0])
		return (FALSE);
	if (ft_strncmp(args[0], "echo", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], "pwd", 3) == 0 && ft_strlen(args[0]) == 3)
		return (TRUE);
	else if (ft_strncmp(args[0], "env", 3) == 0 && ft_strlen(args[0]) == 3)
		return (TRUE);
	else if (ft_strncmp(args[0], "export", 6) == 0 && ft_strlen(args[0]) == 6)
		return (TRUE);
	else if (ft_strncmp(args[0], "cd", 2) == 0 && ft_strlen(args[0]) == 2)
		return (TRUE);
	else if (ft_strncmp(args[0], "exit", 4) == 0 && ft_strlen(args[0]) == 4)
		return (TRUE);
	else if (ft_strncmp(args[0], "unset", 5) == 0 && ft_strlen(args[0]) == 5)
		return (TRUE);
	return (FALSE);
}
