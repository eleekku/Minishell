/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:18:20 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/06 15:46:26 by dzurita          ###   ########.fr       */
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
		exit(127);
	}
	else if (access(path, X_OK) != 0)
	{
		ft_printf(2, "minishell$ %s: Permission denied\n", path);
		close(fd);
		exit(126);
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
	ft_printf(2, "I waited for %d\n", i);
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

	if (cnt->here_doc_fd > 0)
	{
	dup2(cnt->here_doc_fd, STDIN);
	close(cnt->here_doc_fd);
	}
	receive_signal(2);
	child = fork();
		if (child == -1)
			exit (1);
	if (child == 0)
	{
		if (cnt->parse[0].rec_file)
			if (redirect(cnt, 0) < 0)
				exit (1);
		if (args)
			exec(args, cnt->env);
	}
	if (child != 0)
	{
		waitpid(child, &status, 0);
		cnt->exit_status = WEXITSTATUS(status);
	}
}

void	check_here_doc(t_data *cnt)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cnt->parse[i].rec_file)
	{
		while (cnt->parse[i].rec_file[j])
		{
		if (cnt->parse[i].rec_file[j][0] == '<' && cnt->parse[i].rec_file[j][1] == '<')
			here_doc(ft_strchr(cnt->parse[i].rec_file[j], '<') + 2, cnt);
		j++;
		}
		j = 0;
		i++;
	}
}

void	forking(t_data *cnt)
{
	int 	i;
	t_bool	builtin;

	i = 0;
	
	while (i < cnt->i_pipex)
	{
	if (i == 1)
		close (cnt->exec->pipesfd[1]);
	else if (i > 1)
	{
		close (cnt->exec->pipesfd[cnt->exec->fdtrack]);
		close (cnt->exec->pipesfd[(cnt->exec->fdtrack) + 3]);
		ft_printf(2, "I closed %d and %d\n", cnt->exec->pipesfd[cnt->exec->fdtrack], cnt->exec->pipesfd[(cnt->exec->fdtrack) + 3]);
		cnt->exec->fdtrack += 2;
	} 
	builtin = check_built_in(cnt->parse[i].cmd);
	receive_signal(2);
	cnt->exec->child[i] = fork();
	if (cnt->exec->child[i] == 0)
		child_process(cnt, i, builtin);
	i++;
	}
}

void	executor(t_data *cnt)
{
	int	i;

	i = -1;
	if (!cnt->parse)
		return;
	check_here_doc(cnt);
	if (cnt->parse[0].cmd[0] && !cnt->parse[1].cmd && check_built_in(cnt->parse[0].cmd) == TRUE)
	{
		run_builtin(cnt);
		dup2(cnt->stdout_backup, STDOUT);
		close(cnt->stdin_backup);
		cnt->stdout_backup = dup(STDOUT);
		return ;
	}
	if (!cnt->parse[1].cmd)
		single_command(cnt, cnt->parse[0].cmd);
	if (cnt->i_pipex > 1)
	{
	cnt->exec = init_exec_struct(cnt->i_pipex - 1);
	while (++i < cnt->i_pipex)
		piping_and_forking(cnt, i);
	forking(cnt);
	parent_process(cnt);
	}
	if (cnt->here_doc_fd > 0)
	{
		dup2(cnt->stdin_backup, STDIN);
		close(cnt->stdin_backup);
		cnt->stdin_backup = dup(STDIN);
		cnt->here_doc_fd = -1;
	}

}
