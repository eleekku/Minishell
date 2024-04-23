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

int	printchar(int a, int *p, int fd)
{
	if (*p == -1)
		return (-1);
	if (write(fd, &a, 1) == -1)
	{
		*p = -1;
		return (-1);
	}
	else
		return (1);
}

int	checkconvers(const char *format, va_list args, int *p, int fd)
{
	int	chars;

	chars = 0;
	if (*format == 'd' || *format == 'i')
		chars += putints(va_arg(args, int), p, fd);
	if (*format == 's')
		chars += ft_putstr(va_arg(args, char *), p, fd);
	if (*format == 'c')
		chars += printchar(va_arg(args, int), p, fd);
	if (*format == 'u')
		chars += putuints(va_arg(args, unsigned int), p, fd);
	if ((*format == 'x') || (*format == 'X'))
		chars += ft_print_hex(va_arg(args, unsigned int), *format, p, fd);
	if (*format == 'p')
		chars += ft_print_void(va_arg(args, unsigned long long), p, fd);
	if (*format == '%')
		chars += printchar('%', p, fd);
	return (chars);
}

int	ft_printf(int fd, const char *format, ...)
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
			chars += checkconvers(&format[i], args, &p, fd);
		}
		else
			chars += printchar(format[i], &p, fd);
		i++;
	}
	va_end(args);
	if (p == -1)
		return (-1);
	return (chars);
}
