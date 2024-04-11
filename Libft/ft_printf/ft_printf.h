/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:39:35 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/21 16:28:13 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		checkconvers(const char *format, va_list args, int *p);
int		putints(int n, int *p);
int		ft_putstr(char *res, int *p);
int		printchar(int a, int *p);
void	ft_put_hex(unsigned int num, const char format, int *p);
int		ft_hex_len(unsigned int num);
int		ft_print_hex(unsigned int num, const char format, int *p);
int		ft_putnbr(int n, int *p);
int		ft_putnbru(unsigned int n, int *p);
int		putuints(unsigned int n, int *p);
void	ft_put_ptr(uintptr_t num, int *p);
int		ft_ptr_len(uintptr_t num);
int		ft_print_void(unsigned long long ptr, int *p);
#endif
