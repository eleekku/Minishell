/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:01:34 by esalmela          #+#    #+#             */
/*   Updated: 2023/10/28 14:32:37 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int argument)
{
	if ((argument > 64 && argument < 91) || (argument > 96 && argument < 123))
		return (argument);
	else
		return (0);
}
