/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:48:34 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/21 17:26:02 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putnbr(int n, int *p, int fd)
{
	static int	chars;

	chars = 0;
	if (n == -2147483648)
	{
		chars += printchar('-', p, fd);
		chars += printchar('2', p, fd);
		return (ft_putnbr(147483648, p, fd) + 2);
	}
	else if (n < 0)
	{
		chars += printchar('-', p, fd);
		return (ft_putnbr(-n, p, fd) + 1);
	}
	else
	{
		if (n > 9)
			ft_putnbr(n / 10, p, fd);
		chars += printchar((n % 10) + '0', p, fd);
	}
	return (chars);
}

int	ft_putnbru(unsigned int n, int *p, int fd)
{
	static int	chars;

	chars = 0;
	if (n > 9)
		ft_putnbru(n / 10, p, fd);
	chars += printchar((n % 10) + '0', p, fd);
	return (chars);
}

int	ft_putstr(char *res, int *p, int fd)
{
	int	i;

	i = 0;
	if (!res)
		res = "(null)";
	while (res[i] != '\0')
	{
		printchar(res[i], p, fd);
		i++;
	}
	return (i);
}

int	putints(int n, int *p, int fd)
{
	int	len;

	len = ft_putnbr(n, p, fd);
	return (len);
}

int	putuints(unsigned int n, int *p, int fd)
{
	int	len;

	len = ft_putnbru(n, p, fd);
	return (len);
}
