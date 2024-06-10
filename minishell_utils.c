/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:50:46 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/10 17:29:00 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_data_to_parse(t_parse *parse, t_data *data, int i_pipex)
{
	int	i_parse;

	i_parse = 0;
	data->i_parse = i_parse;
	data->i_token = 0;
	data->i_str = 0;
	data->irec = 0;
	while (i_parse < i_pipex)
	{
		count_str_redic(data);
		printf("str : %d\n", data->str);
		parse[i_parse].cmd = safe_calloc(data->str + 1, sizeof(char *));
		parse[i_parse].rec_file = safe_calloc(data->irec + 1, sizeof(char *));
		parse_str(data, parse, i_parse);
		parse_redic(data, parse, i_parse);
		current_itoken(data);
		i_parse++;
		data->i_parse = i_parse;
	}
}

void	update_envp(t_data *content)
{
	char	*lvl;
	int		num;
	int		i;
	char	*tmp;

	i = 0;
	while (content->env[i] && ft_strncmp(content->env[i], "SHLVL=", 6))
		i++;
	num = ft_atoi(content->env[i] + 6);
	tmp = ft_itoa(num + 1);
	lvl = safe_strjoin("SHLVL=", tmp);
	free(tmp);
	i = -1;
	while (content->env[++i])
	{
		if (ft_strncmp(content->env[i], "SHLVL=", 6) == 0)
		{
			free (content->env[i]);
			content->env[i] = lvl;
		}
	}
}

void	create_envp(char **env, t_data *content)
{
	char	**envp;
	int		i;
	int		n;

	n = 0;
	while (env[n])
		n++;
	envp = (char **)malloc(sizeof(char *) * (n + 1));
	i = 0;
	while (i < n)
	{
		envp[i] = ft_strdup(env[i]);
		if (envp[i] == NULL)
			perror("Error al asignar memoria");
		i++;
	}
	envp[i] = NULL;
	content->env = envp;
	update_envp(content);
	content->root = getenv("HOME");
	build_export(content);
}

void	free_struct_parse(t_data *data)
{
	int	i;

	if (!data->parse)
		return ;
	i = 0;
	while (i < data->i_pipex)
	{
		free_args(data->parse[i].cmd);
		free_args(data->parse[i].rec_file);
		i++;
	}
	free(data->parse);
	data->parse = NULL;
	i = 0;
	free (data->lexer_array);
}
