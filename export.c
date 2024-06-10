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

char  *manipulate_variable(t_data *content, int index, char *variable, char *arg)
{
  int i;

  i = 0;
  free(content->exp[index]);
  while (content->env[i] && ft_strncmp(content->env[i], variable, ft_strlen(variable)) != 0)
    i++;
  if (content->env[i] && ft_strncmp(content->env[i], variable, ft_strlen(variable)) == 0 
  && content->env[i][ft_strlen(variable)] == '=')
    {
      free(content->env[i]);
      free(variable);
      content->env[i] = safe_strdup(arg);
      return(safe_strdup(arg));
    }
  content->env = export(arg, content->env);
  free(variable);
  return (safe_strdup(arg));
}

char **export(char *arg, char **table)
{
  int i;
 
  i = 0;
  while (table[i])
    i++;
  table = add_space(table, ft_strlen(arg));
  free(table[i]);
  table[i] = safe_strdup(arg);
  return (table);
}

void  initialize_export2(t_data *content, char *arg)
{
  int i;

  if (ft_strchr(arg, '=') && (*(ft_strchr(arg, '=') + 1)))
		content->env = export(arg, content->env);
  i = 0;
  while(content->exp[i] && ft_strncmp(content->exp[i], arg, ft_strlen(arg)) != 0)
    i++;
  if (!content->exp[i])
    content->exp = export(arg, content->exp);
}

void  initialize_export(t_data *content, char *arg)
{
  int   len;
  int   i;
  char  *variable;

  if (ft_strchr(arg, '='))
  {
    len = ft_strlen(arg) - ft_strlen(ft_strchr(arg, '='));
    variable = ft_substr(arg, 0, len);
    if (!variable)
      exit(1);
    i = 0;
    while (content->exp[i] && ft_strncmp(content->exp[i], variable, len) != 0)
      i++;
    if (content->exp[i])
    { 
      if (ft_strncmp(content->exp[i], arg, ft_strlen(arg)) != 0)
      {
        content->exp[i] = manipulate_variable(content, i, variable, arg);
        return ;
      }
    }
    free (variable);
  }
  initialize_export2(content, arg);
}

void	print_export(t_data *content)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (content->exp[i])
	{
		if (!ft_strchr(content->exp[i], '=') && ft_strlen(content->exp[i]) > 0)
			ft_printf(1, "declare -x %s\n", content->exp[i]);

		else if (ft_strlen(content->exp[i]) > 0)
		{
			while (content->exp[i][j] != '=')
				j++;
			tmp = ft_substr(content->exp[i], 0, j);
				if (!tmp)
					exit(1);
			ft_printf(1, "declare -x %s=\"%s\"\n", tmp, ft_strchr(content->exp[i], '=') + 1);
			free(tmp);
		}
		i++;
		j = 0;
	}
}

void	pre_export(t_data *cnt)
{
	int j;

	j = 0;
	if (!cnt->parse[0].cmd[1])
		print_export(cnt);
	else
		while (cnt->parse[0].cmd[++j])
    {
      if (cnt->parse[0].cmd[j][0] == '=')
        ft_printf(2, "minishell$: export: `%s': not a valid intefier\n", cnt->parse[0].cmd[j]);
      else
			initialize_export(cnt, cnt->parse[0].cmd[j]);
    }
}