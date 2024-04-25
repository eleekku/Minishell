#include "minishell.h"

void  add_spaceenvp(t_data *content, int linel)
{
  int   i;
  int   j;
  char  **new;

  i = 0;
  j = 0;
  while (content->env[i])
    i++;
  new = ft_calloc((i + 2), sizeof(char *)); 
    if (!new)
    perror("Error Malloc env_copy");
      //free
    while (j < i)
    {
      new[j] = ft_strdup(content->env[j]);
      if (!new[i])
          perror("Error Malloc env_copy");
          //free stuff
      j++;
    }
    new[j] = ft_calloc(linel + 1, sizeof(char));
      if (!new[i])
          perror("Error Malloc env_copy");
          //free stuff
    free_args(content->env);
    content->env = new;
}
int export(char **args, t_data *content)
{
  int i;
  char  *data;

  i = 0;
  while (content->env[i])
    i++;
  //data = ft_strnstr(args[1], "=", ft_strlen(args[1]));
 // data++;
  add_spaceenvp(content, ft_strlen(data));
  content->env[i] = args[1];
  return (0);
}
void  built_exit(char **args)
{
  int i;

  ft_printf(1, "exit\n");
  if (!args)
    exit(0);
  else if(ft_atoi(args[0]) == 0 && ft_isdigit(args[0] == 0))
  {
    ft_printf(2, "los_pran: exit: %s: numeric argument required", args[0]);
    args[0] = "255";
  }
  else if (args[1])
    ft_printf(2, "los_pran: exit: too many arguments", args[0]);
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
  char  *argv[0] = "export";
  char  *argv[1] = "testi=kuuluuko";
  export
  //env(&content);
}