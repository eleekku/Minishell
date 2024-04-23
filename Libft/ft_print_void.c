/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_void.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 19:33:15 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/21 17:25:50 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_put_ptr(uintptr_t num, int *p, int fd)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16, p, fd);
		ft_put_ptr(num % 16, p, fd);
	}
	else
	{
		if (num <= 9)
			printchar(num + '0', p, fd);
		else
			printchar(num - 10 + 'a', p, fd);
	}
}

int	ft_ptr_len(uintptr_t num)
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

int	ft_print_void(unsigned long long ptr, int *p, int fd)
{
	int	chars;

	chars = 0;
	chars += printchar('0', p, fd);
	chars += printchar('x', p, fd);
	if (ptr == 0)
		chars += printchar('0', p, fd);
	else
	{
		ft_put_ptr(ptr, p, fd);
		chars += ft_ptr_len(ptr);
	}
	return (chars);
}
