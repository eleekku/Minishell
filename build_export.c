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
	int		len;
	char	**tmp;

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
		content->exp[i] = safe_strjoin("declare -x ", tmp[0]);
		content->exp[i] = safe_strjoin(content->exp[i], "=\"");
		content->exp[i] = safe_strjoin(content->exp[i], tmp[1]);
		content->exp[i] = safe_strjoin(content->exp[i], "\"");
		i++;
		free_args(tmp);
	}
}
