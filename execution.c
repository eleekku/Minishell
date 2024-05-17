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

/* #include "minishell.h"

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
		terminate_program("ft_split", 1);
	}
	path = form_path(temp, cmd, p);
	if (path)
		return (path);
	return (cmd);
}

void	exec(char *cmd, char **envp)
{
	char		**args;
	static char	*path;
	int			p;

	p = 0;
	if (ft_strchr(cmd, 39) != 0)
		args = split_quotations(cmd);
	else
		args = ft_split(cmd, ' ');
	if (!args)
		terminate_program("ft_split", 1);
	if (ft_strchr(args[0], '/') != 0)
		path = args[0];
	else
		path = get_path(args[0], envp, &p);
	//checkpath(path);
	if (path)
		execve(path, args, envp);
	free_args(args);
	exit(127);
}

void	execution(t_data *cnt, int i)
{
	pid_t	child;

	//if (pipe(pipefd) == -1)
		//exit;
	child = fork();
	if (child == -1)
		exit;
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
		exec(cmd, envp);
	}
} */
