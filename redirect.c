/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:37:43 by esalmela          #+#    #+#             */
/*   Updated: 2024/05/29 15:24:11 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limiter, t_data *cnt)
{
	int		pipefd[2];
	char	*line;

	if (cnt->here_doc_fd > 0)
	{
		dup2(cnt->stdin_backup, STDIN);
		close(cnt->stdin_backup);
		cnt->stdin_backup = dup(STDIN);
	}
	if (pipe(pipefd) == -1)
		exit (1);
	while (1)
	{
		receive_signal(1);
		line = readline(" > ");
		if ((g_num == SIGINT) || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break; 
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	free(line);
	cnt->here_doc_fd = pipefd[0];
	dup2(cnt->here_doc_fd, STDIN);
	close(cnt->here_doc_fd);
}

void	open_in_doc(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("minishell$ %s: ", file);
		perror("");
	}
	dup2(fd, STDIN);
	close(fd);
}

int	open_out_doc(char *file, int i)
{
	int	fd;

	if (i == 0)
	{
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_printf(2, "minishell$ %s: ", file);
			perror("");
			return (-1);
		}
	}
	else
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_printf(2, "minishell$ %s: ", file);
			perror("");
			return (-1);
		}
	}
	dup2(fd, STDOUT);
	close(fd);
	return (0);
}

int	redirect(t_data	*cnt, int i)
{
	int j;

	j = -1;
	while (cnt->parse[i].rec_file[++j])
	{
		if (!cnt->parse[i].rec_file[j][1])
		{
			ft_printf(2, "minishell$ : No such file or directory\n");
			return (-1);
		}
		if ((cnt->parse[i].rec_file[j][1] == '$' && cnt->parse[i].rec_file[j][2]) ||
		(cnt->parse[i].rec_file[j][2] == '$' && cnt->parse[i].rec_file[j][3]))
		{
			ft_printf(2, "minishell$ %s: ambigious redirect\n", ft_strchr(cnt->parse[i].rec_file[j], '$'));
			return (-1);
		}
		if (cnt->parse[i].rec_file[j][0] == '>' && cnt->parse[i].rec_file[j][1] != '>')
			return (open_out_doc(((ft_strchr(cnt->parse[i].rec_file[j], '>') + 1)), 1));
		if (cnt->parse[i].rec_file[j][0] == '>' && cnt->parse[i].rec_file[j][1] == '>')
			open_out_doc(((ft_strchr(cnt->parse[i].rec_file[j], '>') + 2)), 0);
		if (cnt->parse[i].rec_file[j][0] == '<' && cnt->parse[i].rec_file[j][1] != '<')
			open_in_doc((ft_strchr(cnt->parse[i].rec_file[j], '<') + 1));
		if (cnt->parse[i].rec_file[j][0] == '<' && cnt->parse[i].rec_file[j][1] == '<')
			here_doc(ft_strchr(cnt->parse[i].rec_file[j], '<') + 2, cnt);	
	}
	return (0);
}
