#include "minishell.h"

int  unset_variable(t_data *content, char **args)
{
    int i;

    i = 0;
	  while (content->env[i] && ft_strncmp(args[1], content->env[i], ft_strlen(args[1])) != 0)
		  i++;
    if (content->env[i])
      free(content->env[i]);
    content->env[i] = ft_strdup("");
    if (!content->env[i])
        return (255);
     i = 0;
    while (content->exp[i] && ft_strncmp(args[1], content->exp[i], ft_strlen(args[1])) != 0)
		  i++;
    if (content->exp[i])
      free(content->exp[i]);
    content->exp[i] = ft_strdup("");
    if (!content->exp[i])
        return (255);
    return (0);
}

void  add_space(char **table, int linel)
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
    new[j] = ft_strdup(table[j]);
    if (!new[j])
        perror("Error Malloc env_copy");
          //free stuff
    j++;
  }
    new[j] = safe_calloc(linel + 1, sizeof(char));
    free_args(table);
    table = new;
}
int export(char *arg, char **table)
{
  int i;
  char  *data;

  i = 0;
  while (table[i])
    i++;
  add_space(table, ft_strlen(arg));
  table[i] = arg;
  
  return (0);
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
    while (content->env[i] && ft_strncmp(content->env[i], variable, len) != 0)
      i++;
    if (ft_strncmp(content->env[i], variable, len) == 0)
      exit (1); //create a function to modify existing variable
  }
  if (ft_strchr(arg, '='))
    export(arg, content->env);
  export(arg, content->exp);
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
    if (ft_strlen(content->env[i]) > 0)
      ft_putendl_fd(content->env[i], 1);
}

/* void  create_envp(char **env, t_data *content)
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
} */

/* int main(int argc, char **argv, char **envp)
{
  t_data content;
  create_envp(envp, &content);
  export(argv, &content);
  env(&content);
  //env(&content);
} */