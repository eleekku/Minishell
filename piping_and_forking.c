/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_and_forking.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:20:31 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/06 15:50:12 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_command(t_data *cnt, char **args, char **env, t_bool builtin)
{
	int piperead;
	int pipewrite;

	ft_printf(2, "piperead is %d\n", cnt->exec->pipesfd[cnt->exec->currentfd - 2]);
	piperead = cnt->exec->pipesfd[cnt->exec->currentfd - 2];
	pipewrite = cnt->exec->pipesfd[cnt->exec->currentfd - 1];
	close(pipewrite);
	dup2(piperead, STDIN);
	close(piperead);
	if (builtin == TRUE)
		run_builtin_child(args, cnt);
	exec(args, env);
}
void	middle_command(t_data *cnt, int i, char **env, t_bool builtin)
{
	int piperead;
	int pipewrite;
	int multiplier;

	multiplier = cnt->i_pipex - (i + 1);
	piperead = cnt->exec->pipesfd[cnt->exec->currentfd - (multiplier * 2 + 2)];
	pipewrite = cnt->exec->pipesfd[cnt->exec->currentfd - (multiplier * 2 - 1)];
	ft_printf(2, "in middle cmd I read from %d and write in %d and multiplier is %d\n", piperead, pipewrite, multiplier);
	dup2(piperead, STDIN);
	dup2(pipewrite, STDOUT);
	close(pipewrite);
	close(piperead);
	if (builtin == TRUE)
		run_builtin_child(cnt->parse[i].cmd, cnt);
	exec(cnt->parse[i].cmd, env);
}
void	first_command(t_data *cnt, char **args, char **env, t_bool builtin)
{
	int	piperead;
	int	pipewrite;

	piperead = cnt->exec->pipesfd[0];
	pipewrite = cnt->exec->pipesfd[1];
	ft_printf(2, "first command I write in %d\n", pipewrite);
	close(piperead);
	dup2(pipewrite, STDOUT);
	close (pipewrite);
	if (builtin == TRUE)
		run_builtin_child(args, cnt);
	exec(args, env);
}

void	child_process(t_data *cnt, int i, t_bool builtin)
{
	receive_signal(2);
	if (g_num == SIGINT || g_num == SIGQUIT)
		exit(1);
	if (i == 1)
		close (cnt->exec->pipesfd[1]);
	else if (i > 1)
	{
		//close (cnt->exec->pipesfd[cnt->exec->fdtrack]);
	//	close (cnt->exec->pipesfd[(cnt->exec->fdtrack) + 3]);
		cnt->exec->fdtrack += 2;
	} 
	if (cnt->parse[i].rec_file[0])
	{
	//	if (i != 0)
			close(cnt->exec->pipesfd[cnt->exec->currentfd - 1]);
			if (redirect(cnt, i) < 0)
				exit (1);
	}
	if (i == 0)
		first_command(cnt, cnt->parse[i].cmd, cnt->env, builtin);
	else if(i > 0 && i < cnt->i_pipex - 1)
		middle_command(cnt, i, cnt->env, builtin);
	else if (i < cnt->i_pipex)
		last_command(cnt, cnt->parse[i].cmd, cnt->env, builtin);
}

void	piping_and_forking(t_data *cnt, int i)
{
	int 	pipefd[2];
	
	if (i < (cnt->i_pipex - 1))
	{
		if (pipe(pipefd) == -1)
			exit (1);
		cnt->exec->pipesfd[cnt->exec->currentfd++] = pipefd[0];
		cnt->exec->pipesfd[cnt->exec->currentfd++] = pipefd[1];
	}
/* 	if (i == 1)
		close (cnt->exec->pipesfd[1]);
	else if (i > 1)
	{
		close (cnt->exec->pipesfd[cnt->exec->fdtrack]);
		close (cnt->exec->pipesfd[(cnt->exec->fdtrack) + 3]);
		cnt->exec->fdtrack += 2;
	} */
	if (cnt->here_doc_fd > 0)
	{
	dup2(cnt->here_doc_fd, STDIN);
	close(cnt->here_doc_fd);
	}
}
