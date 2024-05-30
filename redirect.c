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

void	here_doc(char *limiter)
{
	int		pipefd[2];
	char	*line;
	printf("im here\n");
	pipe(pipefd);
	while (1)//ft_strncmp(line, limiter, ft_strlen(limiter)) != 0
	{
		line = readline(" > ");
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break;
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	//return (pipefd[0]);
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

void	open_out_doc(char *file, int i)
{
	int	fd;

	if (i == 0)
	{
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd == -1)
		{
			printf("minishell$ %s: ", file);
			perror("");
		}
	}
	else
	{
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			printf("minishell$ %s: ", file);
			perror("");
		}
	}
	dup2(fd, STDOUT);
	close(fd);
}

int	redirect(t_data	*cnt, int i)
{
	int j;

	j = -1;
	while (cnt->parse[i].rec_file[++j])
	{
		if ((cnt->parse[i].rec_file[j][1] == '$' && cnt->parse[i].rec_file[j][2]) ||
		(cnt->parse[i].rec_file[j][2] == '$' && cnt->parse[i].rec_file[j][3]))
		{
		ft_printf(2, "minishell$ %s: ambigious redirect\n", ft_strchr(cnt->parse[i].rec_file[j], '$'));
		return (-1);
		}
		if (cnt->parse[i].rec_file[j][0] == '>' && cnt->parse[i].rec_file[j][1] != '>')
			open_out_doc(((ft_strchr(cnt->parse[i].rec_file[j], '>') + 1)), 1);
		if (cnt->parse[i].rec_file[j][0] == '>' && cnt->parse[i].rec_file[j][1] == '>')
			open_out_doc(((ft_strchr(cnt->parse[i].rec_file[j], '>') + 2)), 0);
		if (cnt->parse[i].rec_file[j][0] == '<' && cnt->parse[i].rec_file[j][1] != '<')
			open_in_doc((ft_strchr(cnt->parse[i].rec_file[j], '<') + 1));
		if (cnt->parse[i].rec_file[j][0] == '<' && cnt->parse[i].rec_file[j][1] == '<')
			here_doc(ft_strchr(cnt->parse[i].rec_file[j], '<') + 2);	
	}
	return (0);
}
