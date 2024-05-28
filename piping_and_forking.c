/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:20:31 by esalmela          #+#    #+#             */
/*   Updated: 2024/05/28 18:20:32 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	last_command(t_data *cnt, char **args, char **env, t_bool builtin)
{
	int piperead;
	int pipewrite;

	piperead = cnt->exec->pipesfd[cnt->exec->currentfd - 2];
	pipewrite = cnt->exec->pipesfd[cnt->exec->currentfd - 1];
	close(pipewrite);
	dup2(piperead, STDIN);
	close(piperead);
	if (builtin == TRUE)
		run_builtin_child(args, cnt);
	exec(args, env);
}
void	middle_command(t_data *cnt, char **args, char **env, t_bool builtin)
{
	int piperead;
	int pipewrite;

	piperead = cnt->exec->pipesfd[cnt->exec->currentfd - 4];
	pipewrite = cnt->exec->pipesfd[cnt->exec->currentfd - 1];
	dup2(piperead, STDIN);
	dup2(pipewrite, STDOUT);
	close(pipewrite);
	close(piperead);
	if (builtin == TRUE)
		run_builtin_child(args, cnt);
	exec(args, env);
}
void	first_command(t_data *cnt, char **args, char **env, t_bool builtin)
{
	int	piperead;
	int	pipewrite;

	piperead = cnt->exec->pipesfd[0];
	pipewrite = cnt->exec->pipesfd[1];
	close(piperead);
	dup2(pipewrite, STDOUT);
	close (pipewrite);
	if (builtin == TRUE)
		run_builtin_child(args, cnt);
	exec(args, env);
}

void	child_process(t_data *cnt, int i, int currentfd, t_bool builtin)
{
	if (i == 0)
		first_command(cnt, cnt->parse[i].cmd, cnt->env, builtin);
	else if(i > 0 && i < cnt->i_pipex - 1)
		middle_command(cnt, cnt->parse[i].cmd, cnt->env, builtin);
	else if (i < cnt->i_pipex)
		last_command(cnt, cnt->parse[i].cmd, cnt->env, builtin);
}

void	piping_and_forking(t_data *cnt, int i)
{
	int 	pipefd[2];
	t_bool	builtin;

	if (cnt->parse[i].rec_file[0])
		redirect(cnt, i);
	builtin = check_built_in(cnt->parse[i].cmd);
	if (i < (cnt->i_pipex - 1))
	{
		pipe(pipefd);
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
	cnt->exec->child[i] = fork();
	if (cnt->exec->child[i] == 0)
		child_process(cnt, i, cnt->exec->currentfd, builtin);
}