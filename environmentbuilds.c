#include "minishell.h"

void  add_spaceenvp(char **env, t_data *content, int lines)
{
  int   i;
  char  **new;

  i = 0;
  while (content->env[i])
    i++;
  new = malloc(sizeof(char *) * (i + lines + 1))
  
  
}
int export(char **args, t_data *content)
{
  int i;

  i = 0;
  while (content->env[i])
    i++;
  content->env[i + 1] = malloc((ft_strlen(args[1]) + 1) * sizeof(char))
}
void  exit(char **args)
{
  int i;

  printf(1, "exit\n");
  if (!args)
    exit(0);
  else if(ft_atoi(args[0] == 0 && ft_isdigit(args[0] == 0)))
  {
    printf(2, "los_pran: exit: %s: numeric argument required", args[0]);
    args[0] = "255";
  }
  else if (args[1])
    printf(2, "los_pran: exit: too many arguments", args[0]);
  i = ft_atoi(args[0]);
  if (i < 0 && i >= -256)
    exit(256 + i);
  if (i > 255)
    exit(i % 256);
  if (i < -256)
    exit(256 + (i % 256));
  exit(i);  
}
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