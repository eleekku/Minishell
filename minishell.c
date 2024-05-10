# include "minishell.h"

//think about "heredoc"
/*void  init_lexer(t_data *content, t_lexer *lexer, size_t len, int start)
{
    int i;

    content->lexerarra->start = start;
    content->lexerarra->len = len;
}
void advance(t_lexer* lexer, const char *input) 
{

}

void lexer_tokenize(t_data* data) 
{
    const char  *input = data->str_rl;
    size_t len = ft_strlen(input);
    t_lexer* lexer_array = data->lexerarra;
    int i = 0;
    while (i < len) 
    {
        init_lexer(data, &lexer_array[i], input + i, len - i);
        advance(&lexer_array[i], input);
        i++;
    }
}*/
void just_redirect_final(char *str, int i, int r)
{
  int lf_rg;

  lf_rg = 0;
  while (*str && lf_rg < 2)
  {
      if (*str == '<' && *(++str) == '>')
        lf_rg++;
      str++;
  }
  if (lf_rg == 2)
    printf("%s\n", "minishell: syntax error near unexpected token `<>'");
  else if (r == 3 && i == 1)
      printf("%s\n",  "minishell: syntax error near unexpected token `>'");
  else if (r > 3 && i == 1)
      printf("%s\n",  "minishell: syntax error near unexpected token `>>'");
  else if (i == 4 && r == 1)
      printf("%s\n",  "minishell: syntax error near unexpected token `<'");
  else if (i == 5 && r == 1)
      printf("%s\n",  "minishell: syntax error near unexpected token `<<'");
  else if (i > 5 && r == 1)
      printf("%s\n",  "minishell: syntax error near unexpected token `<<<'");
  else if (r < 2 || i < 3)
      printf("%s\n",  "minishell: syntax error near unexpected token `newline'");
  else if (r > 1 || i > 1)
      printf("%s\n",  "minishell: syntax error");
}
void just_redirect(char *str)
{
  int i;
  int r;
  char *temp;

  if (str[0] == '\0')
    return ;
  i = 1;
  r = 1;
  temp = str;
  if ((*str == '<' || *str == '>') && *(++str) == '\0')
  {
     printf("%s\n",  "minishell: syntax error near unexpected token `newline'");
     return ;
  }
  while (*str)
  {
    if (*str != '<' && *str != '>')
        return ;
    if (*str == '>')
        r++;
    if (*str == '<')
        i++;
    str++;
  }
  just_redirect_final(temp, i, r);
}
void  just_pipes(char *str)
{
   if (str[0] == '\0')
    return ;
  if (*str == '|' && *(++str) == '\0')
  {
     printf("%s\n",  "minishell: syntax error near unexpected token `|'");
     return ;
  }
  while (*str)
  {
    if (*str != '|')
        return ;
    str++;
  }
  printf("%s\n",  "minishell: syntax error near unexpected token `||'");
}
int input_check(t_data *content)
{
    int i;
    t_token *tokens;
    char *str;

    str = content->str_rl;
    just_redirect(str);
    just_pipes(str);  
    lexer_tokenizer(content);
    tokens = content->lexer_array;
    //init_lexer(content);
    return (1);
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
}

/* int main(int ac, char **av, char **envp) 
{
    char* input;
    t_data content;

    if (ac == 0 || ac > 1)
        exit_error("Invalid input\n");
    printf("Welcome to Minishell los pran...\n");
    create_envp(envp, &content);
    //update_envp(&content);
    while ((input = readline("minishell$ ")) != NULL)
    {
      if (strlen(input) > 0) 
        add_history(input);
      content.str_rl = input;
      int in = input_check(&content);//lexer for the parse
      creating_parse(&content);
      //printf("%s\n", input);
      if (ft_strncmp(input, "exit", 4) == 0)
          exit(0);
      free(input);
    }
    printf("hola");
} */
