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

int	ft_putnbr(int n, int *p)
{
	static int	chars;

	chars = 0;
	if (n == -2147483648)
	{
		chars += printchar('-', p);
		chars += printchar('2', p);
		return (ft_putnbr(147483648, p) + 2);
	}
	else if (n < 0)
	{
		chars += printchar('-', p);
		return (ft_putnbr(-n, p) + 1);
	}
	else
	{
		if (n > 9)
			ft_putnbr(n / 10, p);
		chars += printchar((n % 10) + '0', p);
	}
	return (chars);
}

int	ft_putnbru(unsigned int n, int *p)
{
	static int	chars;

	chars = 0;
	if (n > 9)
		ft_putnbru(n / 10, p);
	chars += printchar((n % 10) + '0', p);
	return (chars);
}

int	ft_putstr(char *res, int *p)
{
	int	i;

	i = 0;
	if (!res)
		res = "(null)";
	while (res[i] != '\0')
	{
		printchar(res[i], p);
		i++;
	}
	return (i);
}

int	putints(int n, int *p)
{
	int	len;

	len = ft_putnbr(n, p);
	return (len);
}

int	putuints(unsigned int n, int *p)
{
	int	len;

	len = ft_putnbru(n, p);
	return (len);
}
