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

void	ft_put_ptr(uintptr_t num, int *p)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16, p);
		ft_put_ptr(num % 16, p);
	}
	else
	{
		if (num <= 9)
			printchar(num + '0', p);
		else
			printchar(num - 10 + 'a', p);
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

int	ft_print_void(unsigned long long ptr, int *p)
{
	int	chars;

	chars = 0;
	chars += printchar('0', p);
	chars += printchar('x', p);
	if (ptr == 0)
		chars += printchar('0', p);
	else
	{
		ft_put_ptr(ptr, p);
		chars += ft_ptr_len(ptr);
	}
	return (chars);
}
