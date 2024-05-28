# include "minishell.h"

char  **copy_to_struct(char **table, char **new)
{
  int i;
  int j;

  i = 0;
  j = -1;
  while (new[i])
    i++;
  table = calloc(i + 1, sizeof(char *));
  while (++j < i)
  table[j] = safe_strdup(new[j]);
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

char  **add_space(char **table, int linel)
{
  int   i;
  int   j;
  char  **new;

  i = 0;
  j = 0;
  while (table[i])
    i++;
  new = safe_calloc((i + 2), sizeof(char *));
  while (j < i)
  {
    new[j] = safe_strdup(table[j]);
    if (!new[j])
        perror("Error Malloc env_copy");
          //free stuff
    j++;
  }
  new[j] = safe_calloc(linel + 1, sizeof(char));
  free_array(table);
  table = copy_to_struct(table, new);
  return (table);
}