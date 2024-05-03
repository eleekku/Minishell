/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:12:36 by esalmela          #+#    #+#             */
/*   Updated: 2024/04/29 18:12:38 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishelld.h"

void	build_export(t_data *content)
{
	char	*intro;
	int		i;
	char	**tmp;
	char	*tempstr;

	intro = "declare -x ";
	i = 0;
	while (content->env[i])
		i++;
	content->exp = safe_calloc(i, sizeof(char *));
	i = 0;
	while (content->env[i])
	{
		tmp = ft_split(content->env[i], '=');
			if (!tmp)
			{
				// error stuff
				exit;
			}
		tempstr = safe_strjoin(intro, tmp[0]);
		free(tmp[0]);
		tmp[0] = safe_strjoin(tempstr, "=\"");
		free(tempstr);
		tempstr = safe_strjoin(tmp[0], tmp[1]);
		content->exp[i] = safe_strjoin(tempstr, "\"");
		free(tempstr);
		i++;
		free_args(tmp);
	}
}
