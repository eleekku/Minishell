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

void	exec(char **cmd, t_data *cnt)
{
	char		**args;
	static char	*path;
	int			p;

	p = 0;
//	if (ft_strchr(cmd, 39) != 0)
	//	args = split_quotations(cmd);
//	else
	//	args = ft_split(cmd, ' ');
	//if (!args)
	//	terminate_program("ft_split", 1);
	if (ft_strchr(cmd[0], '/') != 0)
		path = args[0];
	else
		path = get_path(cmd[0], cnt->env, &p);
	//checkpath(path);
	if (path)
		execve(path, cmd, cnt->env);
	//free_args(args);
	exit(127);
}

void	execution(t_data *cnt, int i)
{
	pid_t	child;

	//if (pipe(pipefd) == -1)
		//exit;
	child = fork();
	if (child == -1)
		exit (1);
	if (child != 0)
	{
		//dup2(pipefd[0], STDIN);
	//	close(pipefd[0]);
		waitpid(child, NULL, 0);
		//close(pipefd[1]);
	}
	if (child == 0)
	{
	//	close(pipefd[0]);
	//	dup2(pipefd[1], STDOUT);
	//	close(pipefd[1]);
	//	if (fdin == -1 && index == 2)
	//		exit(127);
		exec(cnt->parse[i].cmd, cnt);
	}
}
