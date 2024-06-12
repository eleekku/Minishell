/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:58:31 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/11 10:02:48 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	here_doc_loop(char *limiter, t_data *cnt, int pipefd)
{
	char	*line;

	while (1)
	{
		line = tcsetreadline(cnt, 1);
		if (g_num == SIGINT)
			break ;
		if (!line)
			return ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		ft_putendl_fd(line, pipefd);
		free(line);
	}
	free(line);
}

void	here_doc(char *limiter, t_data *cnt)
{
	int		pipefd[2];

	receive_signal(1);
	if (cnt->here_doc_fd > 0)
	{
		dup2(cnt->stdin_backup, STDIN);
		close(cnt->stdin_backup);
		cnt->stdin_backup = dup(STDIN);
	}
	if (pipe(pipefd) == -1)
		exit (1);
	here_doc_loop(limiter, cnt, pipefd[1]);
	close(pipefd[1]);
	cnt->here_doc_fd = pipefd[0];
	dup2(cnt->here_doc_fd, STDIN);
	close(cnt->here_doc_fd);
}

void	check_here_doc(t_data *cnt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cnt->parse[i].rec_file)
	{
		while (cnt->parse[i].rec_file[j])
		{
			if (cnt->parse[i].rec_file[j][0] == '<'
				&& cnt->parse[i].rec_file[j][1] == '<')
				here_doc(ft_strchr(cnt->parse[i].rec_file[j], '<') + 2, cnt);
			j++;
		}
		j = 0;
		i++;
	}
}
