/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:54:10 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/07 14:57:59 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/* Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled. 
n: the integer to convert.*/

static int	check_length(int n)
{
	int	length;

	if (n < 0)
		length = 2;
	else
		length = 1;
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static char	*gnresult(long long int temp, int length, char *result, int secneg)
{
	while (length > (0 + secneg))
	{
		result[length - 1] = (temp % 10) + '0';
		temp = temp / 10;
		length--;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	long long int	temp;
	int				length;
	char			*result;
	int				secneg;

	temp = n;
	secneg = 0;
	length = check_length(n);
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	result[length] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		temp *= -1;
		secneg = 1;
	}
	result = gnresult(temp, length, result, secneg);
	return (result);
}
