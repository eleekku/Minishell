/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:18:20 by esalmela          #+#    #+#             */
/*   Updated: 2024/05/24 16:44:49 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
	int j;
	j = 1;
	if (!cnt->parse[i].cmd[1])
		print_export(cnt);
	else
		while (cnt->parse[i].cmd[j])
		{
		if (ft_strchr(cnt->parse[i].cmd[j], '=') && !(ft_strchr(cnt->parse[i].cmd[j], '=') + 1))
			{
				cnt->parse[i].cmd[j] = safe_strjoin(cnt->parse[i].cmd[j], cnt->parse[i].cmd[j + 1]);
				free (cnt->parse[i].cmd[j + 1]);
				j += 2;
			}
		else
		{
			initialize_export(cnt, cnt->parse[i].cmd[j]);
			j++;
		}
		}
	}

void	check_command(t_data *cnt)
{
	int i;
	
	i = 0;
	if (!cnt->parse[i].cmd[0])
	return ;
	if (ft_strncmp(cnt->parse[i].cmd[0], "echo", 4) == 0) // && ft_strlen(cnt->parse[i].cmd[0]) == 4)
		echo(cnt->parse[i].cmd);
	else if (ft_strncmp(cnt->parse[i].cmd[0], "pwd", 3) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 3)
		printf("%s\n", get_pwd());
	else if (ft_strncmp(cnt->parse[i].cmd[0], "env", 3) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 3)
		env(cnt);
	else if (ft_strncmp(cnt->parse[i].cmd[0], "export", 6) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 6)
		pre_export(cnt, i);
	else if (ft_strncmp(cnt->parse[i].cmd[0], "cd", 2) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 2)
		change_directory(cnt->parse[i].cmd[1], cnt);
	else if (ft_strncmp(cnt->parse[i].cmd[0], "exit", 4) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 4)
		built_exit(cnt->parse[i].cmd);
	else if (ft_strncmp(cnt->parse[i].cmd[0], "unset", 5) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 5)
		unset_variable(cnt, cnt->parse[i].cmd);
	else
	last_command(cnt, i); // execution(cnt, i);
}

void	executor(t_data *cnt)
{
	int i;
	int j;
	//int		pipefd[2];
	//pid_t	child;

	/* i = 0;
	if (cnt->parse[1].cmd)
	{
		while(cnt->parse[i + 1].cmd)
		{
			execution(cnt, i);
			i++;
		}
		last_command(cnt, i);
	}
	else */
	if (!cnt->parse)
		return ;
	check_command(cnt);
}

