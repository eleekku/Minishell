#include "minishell.h"

void  env(t_data *content)
{
  int i;

  i = -1;
  while(content->env[++i])
    ft_putendl_fd(content->env[i], 1);
}

void  create_envp(char **env, t_data *content)
{
    char **envp;
    int i;
    int n;

    n = 0;
    while (env[n])
      n++;
    envp = (char **)malloc(sizeof(char *) * n + 1);
    if (!envp)
        perror("Error Mallloc created_envp");
    i = 0;
    while (i < n)
    {
      envp[i] = ft_strdup(env[i]);
      if (envp[i] == NULL)
          perror("Error Mallloc env_copy");
      i++;
    }
    envp[i] = NULL;
    content->env = envp;
}

int main(int argc, char **argv, char **envp)
{
  t_data content;
  create_envp(envp, &content);

  env(&content);
}