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

int	open_doc(char *file, int i)
{
	int	fd;

	if (i == 0)
	{
		fd = open(file, O_RDONLY);
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
	return (fd);
}

void	redirect(t_data	*cnt, int i)
{
	int fdout;
	int j;

	j = -1;
	while (cnt->parse[i].rec_file[++j])
		if (cnt->parse[i].rec_file[j][0] == '>' && cnt->parse[i].rec_file[j][1] != '>')
		{
			fdout = open_doc(((ft_strchr(cnt->parse[i].rec_file[j], '>') + 1)), 1);
		 	dup2(fdout, STDOUT);
			close(fdout);
		}
}