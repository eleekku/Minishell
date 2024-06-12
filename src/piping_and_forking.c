/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_and_forking.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:20:31 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/11 08:47:52 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	last_command(t_data *cnt, int i, char **env, t_bool builtin)
{
	int	piperead;
	int	pipewrite;

	piperead = cnt->exec->pipesfd[cnt->exec->currentfd - 2];
	pipewrite = cnt->exec->pipesfd[cnt->exec->currentfd - 1];
	close(pipewrite);
	dup2(piperead, STDIN);
	close(piperead);
	if (builtin == TRUE)
		run_builtin_child(cnt->parse[i].cmd, cnt);
	exec(cnt->parse[i].cmd, env);
}

void	middle_command(t_data *cnt, int i, char **env, t_bool builtin)
{
	int	piperead;
	int	pipewrite;

	piperead = cnt->exec->pipesfd[cnt->exec->currentfd - 4];
	pipewrite = cnt->exec->pipesfd[cnt->exec->currentfd - 1];
	dup2(piperead, STDIN);
	if (cnt->parse[i].outfile == FALSE)
		dup2(pipewrite, STDOUT);
	close(pipewrite);
	close(piperead);
	if (builtin == TRUE)
		run_builtin_child(cnt->parse[i].cmd, cnt);
	exec(cnt->parse[i].cmd, env);
}

void	first_command(t_data *cnt, int i, char **env, t_bool builtin)
{
	int	piperead;
	int	pipewrite;

	piperead = cnt->exec->pipesfd[0];
	pipewrite = cnt->exec->pipesfd[1];
	close(piperead);
	if (cnt->parse[i].outfile == FALSE)
		dup2(pipewrite, STDOUT);
	close (pipewrite);
	if (builtin == TRUE)
		run_builtin_child(cnt->parse[i].cmd, cnt);
	exec(cnt->parse[i].cmd, env);
}

void	child_process(t_data *cnt, int i, t_bool builtin)
{
	receive_signal(2);
	if (g_num == SIGINT || g_num == SIGQUIT)
		exit(1);
	if (cnt->parse[i].rec_file[0])
	{
		if (redirect(cnt, i) < 0)
			exit (1);
	}
	close(cnt->stdin_backup);
	close(cnt->stdout_backup);
	if (i == 0)
		first_command(cnt, i, cnt->env, builtin);
	else if (i > 0 && i < cnt->i_pipex - 1)
		middle_command(cnt, i, cnt->env, builtin);
	else if (i < cnt->i_pipex)
		last_command(cnt, i, cnt->env, builtin);
}

void	piping_and_forking(t_data *cnt, int i)
{
	int		pipefd[2];
	t_bool	builtin;

	builtin = check_built_in(cnt->parse[i].cmd);
	if (i < (cnt->i_pipex - 1))
	{
		if (pipe(pipefd) == -1)
			exit (1);
		cnt->exec->pipesfd[cnt->exec->currentfd++] = pipefd[0];
		cnt->exec->pipesfd[cnt->exec->currentfd++] = pipefd[1];
	}
	if (i == 1)
		close (cnt->exec->pipesfd[1]);
	else if (i > 1)
	{
		close (cnt->exec->pipesfd[cnt->exec->fdtrack]);
		close (cnt->exec->pipesfd[(cnt->exec->fdtrack) + 3]);
		cnt->exec->fdtrack += 2;
	}
	receive_signal(2);
	cnt->exec->child[i] = fork();
	if (cnt->exec->child[i] == 0)
		child_process(cnt, i, builtin);
}
