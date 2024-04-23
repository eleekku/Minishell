/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:49:32 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/21 17:25:57 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_put_hex(unsigned int num, const char format, int *p, int fd)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, format, p, fd);
		ft_put_hex(num % 16, format, p, fd);
	}
	else
	{
		if (num <= 9)
			printchar(num + '0', p, fd);
		else
		{
			if (format == 'x')
				printchar(num - 10 + 'a', p, fd);
			if (format == 'X')
				printchar(num - 10 + 'A', p, fd);
		}
	}
}

int	ft_hex_len(unsigned int num)
{
	int	i;

	i = 0;
	while (num != 0)
	{
		i++;
		num = num / 16;
	}
	return (i);
}

int	ft_print_hex(unsigned int num, const char format, int *p, int fd)
{
	if (num == 0)
		return (write(fd, "0", 1));
	else
		ft_put_hex(num, format, p, fd);
	return (ft_hex_len(num));
}
