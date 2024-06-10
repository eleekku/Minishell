#include "minishell.h"

void  update_envp(t_data  *content)
{
    char  *lvl;
    int   num;
    int   i;
    char  *tmp;

    i = 0;
    while (content->env[i]  && ft_strncmp(content->env[i], "SHLVL=", 6))
      i++;
    num = ft_atoi(content->env[i] + 6);
    tmp = ft_itoa(num + 1);
    lvl = safe_strjoin("SHLVL=", tmp, content);
    free(tmp);
    i = -1;
    while (content->env[++i])
    {
      if (ft_strncmp(content->env[i], "SHLVL=", 6) == 0)
      {
        free (content->env[i]);
        content->env[i] = lvl;
      }
    }
}

void  create_envp(char **env, t_data *content)
{
    char **envp;
    int i;
    int n;

    n = 0;
    while (env[n])
      n++;
    envp = (char **)malloc(sizeof(char *) * (n + 1));
    i = 0;
    while (i < n)
    {
      envp[i] = safe_strdup(env[i], content);
      i++;
    }
    envp[i] = NULL;
    content->env = envp;
    update_envp(content);
    content->root = getenv("HOME");
    build_export(content);
}
void  free_struct_parse(t_data *data)
{
  int i;

  if (!data->parse)
  {
    if (data->lexer_array)
        free (data->lexer_array);
    return ;
  }
  i = 0;
  while (i < data->i_pipex)
  {
    free_array(data->parse[i].cmd);
    free_array(data->parse[i].rec_file);
    i++;
  }
  free(data->parse);
  data->parse = NULL;
  i = 0;
  free (data->lexer_array);
}