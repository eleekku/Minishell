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

void	pre_export(t_data *cnt)
{
	int j;

	j = 0;
	if (!cnt->parse[0].cmd[1])
		print_export(cnt);
	else
		while (cnt->parse[0].cmd[++j])
			initialize_export(cnt, cnt->parse[0].cmd[j]);
}
void	run_builtin_child(char **args, t_data *cnt)
{
	if (ft_strncmp(args[0], "echo", 4) == 0)
	{
		echo(args);
		exit (0);
	}
	else if (ft_strncmp(args[0], "pwd", 3) == 0 && ft_strlen(args[0]) == 3)
	{
		printf("%s\n", get_pwd());
		exit (0);
	}
	else if (ft_strncmp(args[0], "env", 3) == 0 && ft_strlen(args[0]) == 3)
	{
		env(cnt);
		exit (0);
	}
	else if (ft_strncmp(args[0], "exit", 4) == 0 && ft_strlen(args[0]) == 4)
		built_exit(args);
	exit (0);
}

void	run_builtin(t_data *cnt)
{
	if (!cnt->parse)
		return;
	if (!cnt->parse[0].cmd[0])
		return ;
	if (ft_strncmp(cnt->parse[0].cmd[0], "echo", 4) == 0)
		echo(cnt->parse[0].cmd);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "pwd", 3) == 0 && ft_strlen(cnt->parse[0].cmd[0]) == 3)
		printf("%s\n", get_pwd());
	else if (ft_strncmp(cnt->parse[0].cmd[0], "env", 3) == 0 && ft_strlen(cnt->parse[0].cmd[0]) == 3)
		env(cnt);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "export", 6) == 0 && ft_strlen(cnt->parse[0].cmd[0]) == 6)
		pre_export(cnt);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "cd", 2) == 0 && ft_strlen(cnt->parse[0].cmd[0]) == 2)
		change_directory(cnt->parse[0].cmd[1], cnt);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "exit", 4) == 0 && ft_strlen(cnt->parse[0].cmd[0]) == 4)
		built_exit(cnt->parse[0].cmd);
	else if (ft_strncmp(cnt->parse[0].cmd[0], "unset", 5) == 0 && ft_strlen(cnt->parse[0].cmd[0]) == 5)
		unset_variable(cnt, cnt->parse[0].cmd);
}

t_bool	check_built_in(char **args)
{
	t_bool	value;

	if (!args)
		return (FALSE);
	if (!args[0])
		return (FALSE);
	if (ft_strncmp(args[0], "echo", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], "pwd", 3) == 0 && ft_strlen(args[0]) == 3)
		return (TRUE);
	else if (ft_strncmp(args[0], "env", 3) == 0 && ft_strlen(args[0]) == 3)
		return (TRUE);
	else if (ft_strncmp(args[0], "export", 6) == 0 && ft_strlen(args[0]) == 6)
		return (TRUE);
	else if (ft_strncmp(args[0], "cd", 2) == 0 && ft_strlen(args[0]) == 2)
		return (TRUE);
	else if (ft_strncmp(args[0], "exit", 4) == 0 && ft_strlen(args[0]) == 4)
		return (TRUE);
	else if (ft_strncmp(args[0], "unset", 5) == 0 && ft_strlen(args[0]) == 5)
		return (TRUE);
	return (FALSE);
}

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

t_execute	*init_exec_struct(int pipes)
{
	t_execute	*exec;

	exec = malloc(sizeof(t_execute));
		if (!exec)
			exit(1);
	exec->pipesfd = malloc(((pipes) * 2) * sizeof(int));
		if(!exec->pipesfd)
			exit(1);
	exec->fdtrack = 0;
	exec->currentfd = 0;
	exec->child = malloc((pipes + 1) * sizeof(pid_t));
		if (!exec->child)
			exit(1);
	return (exec);
}

void	single_command(t_data *cnt, char **args)
{
	pid_t	child;
	int		status;

	child = fork();
		if (child == -1)
			exit (1);
	if (child == 0)
		exec(args, cnt->env);
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
