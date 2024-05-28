/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:18:20 by esalmela          #+#    #+#             */
/*   Updated: 2024/05/17 11:11:12 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	pre_export(t_data *cnt, int i)
{
	int j;
	j = 1;
	if (!cnt->parse[i].cmd[1])
		print_export(cnt);
	else
		while (cnt->parse[i].cmd[j])
		{
	/* 	if (ft_strchr(cnt->parse[i].cmd[j], '=')) // && !(ft_strchr(cnt->parse[i].cmd[j], '=') + 1))
			{
				cnt->parse[i].cmd[j] = safe_strjoin(cnt->parse[i].cmd[j], cnt->parse[i].cmd[j + 1]);
				free (cnt->parse[i].cmd[j + 1]);
				j += 2;
			}
		else
		{ */
			initialize_export(cnt, cnt->parse[i].cmd[j]);
			j++;
		}
	//	}
}

void	check_command(t_data *cnt)
{
	int i;
	pid_t	child;
	i = 0;
	if (!cnt->parse)
		return;
	if (!cnt->parse[i].cmd[0])
		return ;
	if (ft_strncmp(cnt->parse[i].cmd[0], "echo", 4) == 0) // && ft_strlen(cnt->parse[i].cmd[0]) == 4)
		echo(cnt->parse[i].cmd);
	else if (ft_strncmp(cnt->parse[i].cmd[0], "pwd", 3) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 3)
		printf("%s\n", get_pwd());
	else if (ft_strncmp(cnt->parse[i].cmd[0], "env", 3) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 3)
		env(cnt);
	else if (ft_strncmp(cnt->parse[i].cmd[0], "export", 6) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 6)
		pre_export(cnt, i);
	else if (ft_strncmp(cnt->parse[i].cmd[0], "cd", 2) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 2)
		change_directory(cnt->parse[i].cmd[1], cnt);
	else if (ft_strncmp(cnt->parse[i].cmd[0], "exit", 4) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 4)
		built_exit(cnt->parse[i].cmd);
	else if (ft_strncmp(cnt->parse[i].cmd[0], "unset", 5) == 0 && ft_strlen(cnt->parse[i].cmd[0]) == 5)
		unset_variable(cnt, cnt->parse[i].cmd);
	else
	{
	child = fork();
	if (child == 0)
		exec(cnt->parse[i].cmd, cnt->env);
	waitpid(child, NULL, 0);
	} // execution(cnt, i);
}

void	last_command(t_data *cnt, char **args, char **env)
{
	int piperead;
	int pipewrite;

	piperead = cnt->exec->pipesfd[cnt->exec->currentfd - 2];
	pipewrite = cnt->exec->pipesfd[cnt->exec->currentfd - 1];
	close(pipewrite);
	dup2(piperead, STDIN);
	close(piperead);
	exec(args, env);
}
void	middle_command(int j, int *pipesfd, char **args, char **env)
{
	int piperead = pipesfd[j - 4];
	int pipewrite = pipesfd[j - 1];
	
	dup2(piperead, STDIN);
	dup2(pipewrite, STDOUT);
	close(pipewrite);
	close(piperead);
	exec(args, env);
}
void	first_command(int piperead, int pipewrite, char **args, char **env)
{
	close(piperead);
	dup2(pipewrite, STDOUT);
	close (pipewrite);
	exec(args, env);
}

void	child_process(t_data *cnt, int i, int currentfd)
{
	if (i == 0)
		first_command(cnt->exec->pipesfd[0], cnt->exec->pipesfd[1], cnt->parse[i].cmd, cnt->env);
	else if(i > 0 && i < cnt->i_pipex - 1)
		middle_command(currentfd, cnt->exec->pipesfd, cnt->parse[i].cmd, cnt->env);
	else if (i < cnt->i_pipex)
		last_command(cnt, cnt->parse[i].cmd, cnt->env);
}

void	piping_and_forking(t_data *cnt, int i)
{
	int pipefd[2];

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
			child_process(cnt, i, cnt->exec->currentfd);
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
}
void	executor(t_data *cnt)
{
	int 		i;
	t_execute	*exec;

	exec = malloc(sizeof(t_execute));
	if (!exec)
		exit(1);
	exec->pipesfd = malloc(((cnt->i_pipex - 1) * 2) * sizeof(int));
		if(!exec->pipesfd)
			exit(1);
	i = -1;
	exec->fdtrack = 0;
	exec->currentfd = 0;
	exec->child = malloc(cnt->i_pipex * sizeof(pid_t));
		if (!exec->child)
			exit(1);
	cnt->exec = exec;
	while (++i < cnt->i_pipex)
	piping_and_forking(cnt, i);
	parent_process(cnt);
}
