/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:31:12 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/11 08:49:13 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	checkpath(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd != -1)
	{
		ft_printf(2, "minishell$ %s: is a directory\n", path);
		return (126);
	}
	else if (access(path, F_OK) != 0)
	{
		if (ft_strchr(path, '/') != 0)
			ft_printf(2, "minishell$ %s: No such file or directory\n", path);
		else
			ft_printf(2, "minishell$ %s: command not found\n", path);
		close(fd);
		return (127);
	}
	else if (access(path, X_OK) != 0)
	{
		ft_printf(2, "minishell$ %s: Permission denied\n", path);
		close(fd);
		return (126);
	}
	return (0);
}

t_execute	*init_exec_struct(int pipes)
{
	t_execute	*exec;

	exec = malloc(sizeof(t_execute));
	if (!exec)
		exit(1);
	exec->pipesfd = malloc(((pipes) * 2) * sizeof(int));
	if (!exec->pipesfd)
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
	temp = ft_strjoin(path, "/");
	if (!temp)
		ft_printf(2,
			"minishell$: fatal error with malloc in child process\n");
	path = ft_strjoin(temp, cmd);
	free(temp);
	if (!path)
		ft_printf(2,
			"minishell$: fatal error with malloc in child process\n");
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
				free_array(path_temp);
				return (path);
			}
		}
		if (path)
			free(path);
		i++;
	}
	free_array(path_temp);
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
	temp = ft_split(envp[i] + 5, ':');
	if (!temp)
	{
		ft_printf(2, "minishell$: fatal error with malloc in child process\n");
		exit(1);
	}
	path = form_path(temp, cmd, p);
	if (path)
		return (path);
	return (cmd);
}
