# include "minishell.h"

char  **copy_to_struct(char **table, char **new, t_data *content)
{
  int i;
  int j;

  i = 0;
  j = -1;
  while (new[i])
    i++;
  table = safe_calloc(i + 1, sizeof(char *), content);
  while (++j < i)
  table[j] = safe_strdup(new[j], content);
  free_array(new);
  return (table);
}

void  free_array(char **args)
{
  int i;

  i = 0;
  while(args[i])
  {
    free(args[i]);
    i++;
  }
  free (args);
}

void	build_export(t_data *content)
{
	int		i;

	i = 0; 
	while (content->env[i])
		i++;
	content->exp = safe_calloc(i + 1, sizeof(char *), content);
	i = 0;
	while (content->env[i])
	{
		content->exp[i] = ft_strdup(content->env[i]);
			if (!content->exp[i])
			{
				ft_printf(2, "minishell$: fatal error with malloc\n");
				prepare_exit(content, 1);
			}
		i++;
	}
	content->exp[i] = NULL;
}

char  **add_space(char **table, int linel, t_data *content)
{
  int   i;
  int   j;
  char  **new;

  i = 0;
  j = 0;
  while (table[i])
    i++;
  new = safe_calloc((i + 2), sizeof(char *), content);
  while (j < i)
  {
    new[j] = safe_strdup(table[j], content);
    if (!new[j])
        perror("Error Malloc env_copy");
          //free stuff
    j++;
  }
  new[j] = safe_calloc(linel + 1, sizeof(char), content);
  free_array(table);
  table = copy_to_struct(table, new, content);
  return (table);
}