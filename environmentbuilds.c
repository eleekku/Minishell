#include "minishell.h"

int unset_variable(t_data *content, char **args)
{
    int i;

    i = 0;
	  while (content->env[i] && ft_strncmp(args[1], content->env[i], ft_strlen(args[1])) != 0)
		  i++;
    if (content->env[i])
    {
    free(content->env[i]);
    content->env[i] = safe_strdup("");
    }
   // if (!content->env[i])
       // return (255);
     i = 0;
    while (content->exp[i] && ft_strncmp(args[1], content->exp[i], ft_strlen(args[1])) != 0)
		  i++;
    if (content->exp[i])
    {
      free(content->exp[i]);
      content->exp[i] = safe_strdup("");
    }
    if (!content->exp[i])
        return (255);
    return (0);
}

void  built_exit(char **args)
{
  int i;

  ft_printf(1, "exit\n");
  if (!args)
    exit(0);
  else if(ft_atoi(args[1]) == 0 && ft_isdigit(args[1] == 0))
  {
    ft_printf(2, "minishell$: exit: %s: numeric argument required", args[1]);
    args[0] = "255";
  }
  else if (args[2])
    ft_printf(2, "minishell$: exit: too many arguments", args[1]);
  i = ft_atoi(args[1]);
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
  {
    if (content->env[i] && ft_strlen(content->env[i]) > 0)
      ft_putendl_fd(content->env[i], 1);
  }
}
