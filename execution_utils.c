/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:31:12 by esalmela          #+#    #+#             */
/*   Updated: 2024/05/17 14:31:15 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 #include "minishell.h"

t_execute	*init_exec_struct(int pipes)
{
	t_execute	*exec;

	exec = malloc(sizeof(t_execute));
		if (!exec)
			exit(1);
	exec->pipesfd = malloc(((pipes) * 2) * sizeof(int));
		if(!exec->pipesfd)
			exit(1);
	exec->fdtrack = 0;
	exec->currentfd = 0;
	exec->child = malloc((pipes + 1) * sizeof(pid_t));
		if (!exec->child)
			exit(1);
	return (exec);
}

char	*create_string(char *path, char *cmd)
{
	char	*temp;

	if (!path || !cmd)
		return (cmd);
	temp = safe_strjoin(path, "/");
	path = safe_strjoin(temp, cmd);
	free(temp);
	return (path);
}

char	*form_path(char **path_temp, char *cmd, int *p)
{
	int		i;
	char	*path;

	i = 0;
	while (path_temp[i])
	{
		path = create_string(path_temp[i], cmd);
		if (path)
		{
			if (access(path, F_OK) == 0)
			{
				*p = -1;
				free_args(path_temp);
				return (path);
			}
		}
		free(path);
		i++;
	}
	free_args(path_temp);
	return (NULL);
}

char	*get_path(char *cmd, char **envp, int *p)
{
	int		i;
	char	**temp;
	char	*path;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (!envp[i])
		return (cmd);
	envp[i] = envp[i] + 5;
	temp = ft_split(envp[i], ':');
	if (!temp)
	{
		exit (1);
	//	terminate_program("ft_split", 1);
	}
	path = form_path(temp, cmd, p);
	if (path)
		return (path);
	return (cmd);
}
