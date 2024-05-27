# include "minishell.h"
#include <errno.h>
//think about "heredoc"

int  just_pipes(char *str)
{
  if (str[0] == '\0')
    return (1);
  if (*str == '|' && ft_strlen(str) == 1)
  {
     printf("%s\n",  "minishell: syntax error near unexpected token `|'");
     return (1);
  }
  if (*str == '|' && *str++ == '|')
  {
      printf("%s\n",  "minishell: syntax error near unexpected token `||'");
      return (1);
  }
  return (0);
}

int input_check(t_data *content)
{
    int i;
    t_token *tokens;
    char *str;

    str = content->str_rl;
    int error = just_pipes(str);
    if (error)
        return (1);
    lexer_tokenizer(content);
    tokens = content->lexer_array;
    ///////////////////////print tokens\\\\\\\\\\\\\\\\\\\\\\\\\/
    i = 0;
    while (tokens[i].type != TOKEN_EOL)
    {
      printf("Token %d: Type %d, Start %s, Len %zu\n", i, tokens[i].type, tokens[i].pos.start, tokens[i].pos.len);
      i++;
    }
    //init_lexer(content);
    return (0);
}
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
    envp = (char **)malloc(sizeof(char *) * (n + 1));
    i = 0;
    while (i < n)
    {
      envp[i] = ft_strdup(env[i]);
      if (envp[i] == NULL)
          perror("Error al asignar memoria");
      i++;
    }
    envp[i] = NULL;
    content->env = envp;
    content->root = get_root();
    build_export(content);
}

int main(int ac, char **av, char **envp) //arreglar problemas cuando tengo pipes y nada luego
{
    char* input;
    t_data content;

    content.exit_error = 127;
    if (ac == 0 || ac > 1)
        exit_error("Invalid input\n");
    printf("Welcome to Minishell los pran...\n");
    create_envp(envp, &content);
    //update_envp(&content);
    while (1)// (input = readline("minishell$ ")) != NULL)
    {
      input = readline("minishell$ ");
     if (input && ft_strlen(input) > 0) 
        add_history(input);
      content.str_rl = input;
      int in = input_check(&content);//lexer for the parse
      if (in == 0)
        creating_parse(&content);
      //executor(&content);
     //check_command(&content);
      //printf("%s\n", input);
      if (ft_strncmp(input, "exit", 4) == 0)
          exit(0);
      free(input);
    }
}