/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_doble_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:16:16 by dzurita           #+#    #+#             */
/*   Updated: 2024/04/24 16:16:19 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_split_result(char **split_result)
{
	char	**temp;

	if (!split_result || !*split_result)
		return ;
	temp = split_result;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(split_result);
}
