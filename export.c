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
//#include "minishelld.h"

char **export(char *arg, char **table)
{
  int i;
  char  *data;
  i = 0;
  while (table[i])
    i++;
  table = add_space(table, ft_strlen(arg));
  table[i] = ft_strdup(arg);
  return (table);
}

char  *manipulate_variable(t_data *content, int index, char *variable, char *arg)
{
  int i;

  i = 0;
 // printf("%p\n", content->exp[index]);
  free(content->exp[index]);
  content->exp[index] = ft_strdup(arg);
 // printf("%p\n", content->exp[index]);
    if (!content->exp[index])
      exit(1); //errooooor
  while (content->env[i] && ft_strncmp(content->env[i], variable, ft_strlen(variable)) != 0)
    i++;
  if (content->env[i] && ft_strncmp(content->env[i], variable, ft_strlen(variable)) == 0)
    {
      free(content->env[i]);
      content->env[i] = ft_strdup(arg);
      return(ft_strdup(arg));
    }
  content->env = export(arg, content->env);
  return (ft_strdup(arg));
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
    if (content->exp[i]) //ft_strncmp(content->env[i], variable, len) == 0)
    { 
      if (ft_strncmp(content->exp[i], arg, ft_strlen(arg)) != 0)
      {
        content->exp[i] = manipulate_variable(content, i, variable, arg);
        return ;
      }
    }
  }
  if (ft_strchr(arg, '='))
    content->env = export(arg, content->env);
  i = 1;
  while(content->exp[i] && ft_strncmp(content->exp[i], arg, ft_strlen(arg)) != 0)
  i++;
  if (!content->exp[i])
    content->exp = export(arg, content->exp);
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

void	build_export(t_data *content)
{
	int		i;

	i = 0; 
	while (content->env[i])
		i++;
	content->exp = safe_calloc(i + 1, sizeof(char *));
	i = 0;
	while (content->env[i])
	{
		content->exp[i] = ft_strdup(content->env[i]);
			if (!content->exp[i])
			{
				// error stuff
				exit(255);
			}
		i++;
	}
	content->exp[i] = NULL;
}

/* int	main(int argc, char **argv, char **envp)
{
	char	**arr;
	t_data content;
	int	i;

	i = -1;
	create_envp(envp, &content);
	build_export(&content);
	unset_variable(&content, ft_split("unset MAIL", ' '));
	env(&content);
	print_export(&content);
	
	while (content.env[++i])
		printf("%s\n", content.env[i]);
	 i = 0;
	while (i < content.exp[i])
	{
		printf("%s\n", content.exp[i]);
		i++;
	} 
} */
