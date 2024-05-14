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
	int i;
	char *temp;

	i = 2;
	while (args[i + 1])
	{
		temp = safe_strjoin(temp, args[i]);
		i++;
	}
}
void	check_command(t_data *cnt, int i)
{
	int j;

	if (ft_strncmp(cnt->parse[i].cmd[0], "echo", 4) == 0)
		echo(cnt->parse[i].cmd);
	if (ft_strncmp(cnt->parse[i].cmd[0], "pwd", 3) == 0)
		printf("%s\n", get_pwd());
	if (ft_strncmp(cnt->parse[i].cmd[0], "env", 3) == 0)
		env(cnt);
	if (ft_strncmp(cnt->parse[i].cmd[0], "export", 6) == 0)
	{
		if (!cnt->parse[i].cmd[1])
			print_export(cnt);
		else
			initialize_export(cnt, cnt->parse[i].cmd[1]); 
	}
}
