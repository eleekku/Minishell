/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:18:25 by esalmela          #+#    #+#             */
/*   Updated: 2024/02/07 15:35:55 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	set_them_free(char *a, char *b)
{
	free(a);
	free(b);
}

char	*read_line(int fd, char *save)
{
	char	*buff;
	int		bytes_read;

	if (ft_strchr(save, '\n'))
		return (save);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
	{
		free(save);
		return (NULL);
	}
	bytes_read = 1;
	while (!ft_strchr(save, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			set_them_free(save, buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		save = ft_strjoingnl(save, buff);
	}
	free(buff);
	return (save);
}

char	*give_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_save(char *save)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	str = malloc((ft_strlen(save) - i + 1) * sizeof(char));
	if (!str)
	{
		free(save);
		return (NULL);
	}
	i++;
	j = 0;
	while (save[i])
		str[j++] = save[i++];
	str[j] = '\0';
	free(save);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_line(fd, save);
	if (!save)
		return (0);
	line = give_line(save);
	save = ft_save(save);
	if (ft_strlen(line) == 0)
	{
		set_them_free(save, line);
		save = NULL;
		return (NULL);
	}
	return (line);
}
