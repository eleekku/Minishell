/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:10:32 by esalmela          #+#    #+#             */
/*   Updated: 2023/11/06 14:28:38 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int argument)
{
	if ((argument >= '0' && argument <= '9')
		|| ((argument >= 'A' && argument <= 'Z')
			|| (argument >= 'a' && argument <= 'z')))
		return (1);
	else
		return (0);
}
