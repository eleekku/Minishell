# include "minishelld.h"

//think about "heredoc"

/*int input_check(t_data *content)
{
  //lexer stuff
}*/
void exit_error(char *str)
{
  printf("%s\n", str);
  exit(1);
}
void  update_envp(t_data  *content)
{
  char **envp;
  char *lvl;
  int num;
  int i;

  envp = content->env;
  i = 0;
  while (envp[i]  && ft_strncmp(envp[i], "SHLVL=", 6))
    i++;
  num = ft_atoi(envp[i] + 6);
  lvl = ft_strjoin("SHLVL=", ft_itoa(num + 1));
  if (!lvl)
  {
    //free envp;
    exit_error("Error Malloc SHLVL");
  }
  i = -1;
  while (envp[++i])
  {
    if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
    {
      free (envp[i]);
      envp[i] = lvl;
      free (lvl);
    }
    printf("%s\n", envp[i]);
  }
  content->env = envp;
}
void  create_envp(char **env, t_data *content)
{
  char **envp;
  int i;
  int n;

  n = 0;
  while (env[n])
    n++;
  envp = (char **)malloc(sizeof(char *) * n);
  i = 0;
  while (i < n)
  {
    envp[i] = ft_strdup(env[i]);
    if (envp[i] == NULL)
        perror("Error al asignar memoria");
    i++;
  }
  content->env = envp;
}

int main(int ac, char **av, char **envp) 
{
  char* input;
  t_data content;

  if (ac == 0 || ac > 1)
      exit_error("Invalid input\n");
  printf("Welcome to Minishell los pran...\n");
  create_envp(envp, &content);
  update_envp(&content);
  /*while ((input = readline("minishell$ ")) != NULL) 
  {
    if (strlen(input) > 0) 
      add_history(input);
    content.str_rl = &input;
    input_check(&content);//lexer for the parse
    printf("%s\n", input);
    free(input);
  }*/
  return (0);
}
