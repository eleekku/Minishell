/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:18:20 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/04 14:59:28 by esalmela          ##     #   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checkpath(char *path)
{
	int	fd;

	if (!path)
		exit (0);
	fd = open(path, O_DIRECTORY);
	if (fd != -1 && path[0] == '.')
	{
		ft_printf(2, "minishell$ %s: is a directory\n", path);
		exit(126);
	}
	else if (access(path, F_OK) != 0)
	{
		if (ft_strchr(path, '/') != 0)
			ft_printf(2, "minishell$ %s: No such file or directory\n", path);
		else
			ft_printf(2, "minishell$ %s: command not found\n", path);
		close(fd);
		exit (127);
	}
	else if (access(path, X_OK) != 0)
	{
		ft_printf(2, "minishell$ %s: Permission denied\n", path);
		close(fd);
		exit (126);
	}
}

void	exec(char **cmd, char **env)
{
	static char	*path;
	int			p;

	p = 0;
	if (ft_strchr(cmd[0], '/') != 0)
		path = cmd[0];
	else
		path = get_path(cmd[0], env, &p);
	checkpath(path);
	if (path)
		execve(path, cmd, env);
	exit(127);
}

void	parent_process(t_data *cnt)
{
	int i;
	int status;

	status = 0;
	i = 0;
	while (i < cnt->i_pipex)
	{
	waitpid(cnt->exec->child[i], &status, 0);
	cnt->exit_status = WEXITSTATUS(status);
	i++;
	}
	close(cnt->exec->pipesfd[cnt->exec->currentfd - 2]);
	free(cnt->exec->child);
	free(cnt->exec->pipesfd);
	free(cnt->exec);
}

void	single_command(t_data *cnt, char **args)
{
	pid_t	child;
	int		status;

	child = fork();
		if (child == -1)
			exit (1);
	if (child == 0)
	{
		if (cnt->parse[0].rec_file[0])
			cnt->exit_status = redirect(cnt, 0);
		exec(args, cnt->env);
	}
	if (child != 0)
	{
		waitpid(child, &status, 0);
		cnt->exit_status = WEXITSTATUS(status);
	}
}

void	executor(t_data *cnt)
{
	int	i;

	i = -1;
	if (!cnt->parse || !cnt->parse[0].cmd[0])
		return;
	if (!cnt->parse[1].cmd && check_built_in(cnt->parse[0].cmd) == TRUE)
	{
		run_builtin(cnt);
		return ;
	}
	if (!cnt->parse[1].cmd)
		single_command(cnt, cnt->parse[0].cmd);
	if (cnt->i_pipex > 1)
	{
	cnt->exec = init_exec_struct(cnt->i_pipex - 1);
	while (++i < cnt->i_pipex)
		piping_and_forking(cnt, i);
	parent_process(cnt);
	}
	//nothing
}
