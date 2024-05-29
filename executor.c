/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:18:20 by esalmela          #+#    #+#             */
/*   Updated: 2024/05/29 13:25:01 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	exec(char **cmd, char **env)
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
		path = get_path(cmd[0], env, &p);
	//checkpath(path);
	if (path)
		execve(path, cmd, env);
	//free_args(args);
	exit(127);
}

void	parent_process(t_data *cnt)
{
	int i;
	int status;

	i = 0;
	while (i < cnt->i_pipex)
	{
	waitpid(cnt->exec->child[i], &status, 0);
	cnt->exit_status = status;
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
			redirect(cnt, 0);
		exec(args, cnt->env);
	}
	if (child != 0)
	{
		waitpid(child, &status, 0);
		cnt->exit_status = status;
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
}
