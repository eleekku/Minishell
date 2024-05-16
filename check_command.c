/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:18:20 by esalmela          #+#    #+#             */
/*   Updated: 2024/05/13 16:18:22 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	pre_echo(char	**args)
{
	int		i;
	char	*temp;

	i = 2;
	while (args[i + 1])
	{
		temp = safe_strjoin(temp, args[i]);
		i++;
	}
}
void	pre_export(t_data *cnt, int i)
{
	if (!cnt->parse[i].cmd[1])
		print_export(cnt);
	else
		if (!(ft_strchr(cnt->parse[i].cmd[1], '=') + 1))
			{
				cnt->parse[i].cmd[1] = safe_strjoin(cnt->parse[i].cmd[1], cnt->parse[i].cmd[2]);
				free (cnt->parse[i].cmd[2]);
			}
			initialize_export(cnt, cnt->parse[i].cmd[1]); 
	}

void	check_command(t_data *cnt, int i)
{
	if (ft_strncmp(cnt->parse[i].cmd[0], "echo", 4) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 4)
		echo(cnt->parse[i].cmd);
	if (ft_strncmp(cnt->parse[i].cmd[0], "pwd", 3) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 3)
		printf("%s\n", get_pwd());
	if (ft_strncmp(cnt->parse[i].cmd[0], "env", 3) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 3)
		env(cnt);
	if (ft_strncmp(cnt->parse[i].cmd[0], "export", 6) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 6)
		pre_export(cnt, i);
	if (ft_strncmp(cnt->parse[i].cmd[0], "cd", 2) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 2)
		change_directory(cnt->parse[i].cmd[1], cnt);
	if (ft_strncmp(cnt->parse[i].cmd[0], "exit", 4) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 4)
		built_exit(cnt->parse[i].cmd);
	if (ft_strncmp(cnt->parse[i].cmd[0], "unset", 5) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 5)
		unset_variable(cnt, cnt->parse[i].cmd);
}
