/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:37:43 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/11 09:53:12 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	open_in_doc(char *file, t_data *cnt, int i)
{
	int	fd;

	cnt->parse[i].infile = TRUE;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "minishell$ %s: ", file);
		perror("");
		return (-1);
	}
	dup2(fd, STDIN);
	close(fd);
	return (0);
}

int	open_out_doc(char *file, int dirtype, t_data *cnt, int i)
{
	int	fd;

	cnt->parse[i].outfile = TRUE;
	if (dirtype == 0)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf(2, "minishell$ %s: ", file);
		perror("");
		return (-1);
	}
	dup2(fd, STDOUT);
	close(fd);
	return (0);
}

int	doc_error(t_data *cnt, int i, int j)
{
	if (cnt->parse[i].rec_file[j][0] == '<'
		&& cnt->parse[i].rec_file[j][1] == '<')
		return (0);
	if (!cnt->parse[i].rec_file[j][1])
	{
		ft_printf(2, "minishell$ : No such file or directory\n");
		return (-1);
	}
	if ((cnt->parse[i].rec_file[j][1] == '$'
		&& cnt->parse[i].rec_file[j][2])
		|| (cnt->parse[i].rec_file[j][2] == '$'
		&& cnt->parse[i].rec_file[j][3]))
	{
		ft_printf(2, "minishell$ %s: ambigious redirect\n",
			ft_strchr(cnt->parse[i].rec_file[j], '$'));
		return (-1);
	}
	return (0);
}

int	redirect(t_data	*cnt, int i)
{
	int	j;

	j = -1;
	while (cnt->parse[i].rec_file[++j])
	{
		if (doc_error(cnt, i, j) < 0)
			return (-1);
		if (cnt->parse[i].rec_file[j][0] == '>'
		&& cnt->parse[i].rec_file[j][1] != '>')
			return (open_out_doc(((ft_strchr(cnt->parse[i].rec_file[j],
								'>') + 1)), 1, cnt, i));
		if (cnt->parse[i].rec_file[j][0] == '>'
		&& cnt->parse[i].rec_file[j][1] == '>')
			return (open_out_doc(((ft_strchr(cnt->parse[i].rec_file[j],
								'>') + 2)), 0, cnt, i));
		if (cnt->parse[i].rec_file[j][0] == '<' && cnt->parse[i].rec_file[j][1]
		!= '<')
			return (open_in_doc((ft_strchr(cnt->parse[i].rec_file[j], '<') + 1),
					cnt, i));
	}
	return (0);
}
