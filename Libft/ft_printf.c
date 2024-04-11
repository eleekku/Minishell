/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:18:51 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/22 14:10:24 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	printchar(int a, int *p)
{
	if (*p == -1)
		return (-1);
	if (write(1, &a, 1) == -1)
	{
		*p = -1;
		return (-1);
	}
	else
		return (1);
}

int	checkconvers(const char *format, va_list args, int *p)
{
	int	chars;

	chars = 0;
	if (*format == 'd' || *format == 'i')
		chars += putints(va_arg(args, int), p);
	if (*format == 's')
		chars += ft_putstr(va_arg(args, char *), p);
	if (*format == 'c')
		chars += printchar(va_arg(args, int), p);
	if (*format == 'u')
		chars += putuints(va_arg(args, unsigned int), p);
	if ((*format == 'x') || (*format == 'X'))
		chars += ft_print_hex(va_arg(args, unsigned int), *format, p);
	if (*format == 'p')
		chars += ft_print_void(va_arg(args, unsigned long long), p);
	if (*format == '%')
		chars += printchar('%', p);
	return (chars);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;
	int		chars;
	int		p;

	p = 1;
	chars = 0;
	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			chars += checkconvers(&format[i], args, &p);
		}
		else
			chars += printchar(format[i], &p);
		i++;
	}
	va_end(args);
	if (p == -1)
		return (-1);
	return (chars);
}
