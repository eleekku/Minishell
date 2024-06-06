# include "minishell.h"

int	g_num;

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
    char  *lvl;
    int   num;
    int   i;
    char  *tmp;

    i = 0;
    while (content->env[i]  && ft_strncmp(content->env[i], "SHLVL=", 6))
      i++;
    num = ft_atoi(content->env[i] + 6);
    tmp = ft_itoa(num + 1);
    lvl = safe_strjoin("SHLVL=", tmp);
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
      envp[i] = ft_strdup(env[i]);
      if (envp[i] == NULL)
          perror("Error al asignar memoria");
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
  //while (data->lexer_array[i].type != TOKEN_EOL)
  //{
  //  free (data->lexer_array[i].pos.start);
  //  i++;
  //}
  //free (data->lexer_array[i].pos.start);
  free (data->lexer_array);
}

int main(int ac, char **av, char **envp) //need to fix parse >""hola""
{
    char* input;
    int in;
    t_data content;

    //ac = 0;
    (void)av;
    content.exit_status = 127;
    content.here_doc_fd = -1;
    content.stdin_backup = dup(STDIN);
    content.stdout_backup = dup(STDOUT);
    if (ac != 1)
        exit_error("Invalid input\n");
    printf("Welcome to Minishell los pran...\n");
    create_envp(envp, &content);
    load_termios(&content);
    //update_envp(&content);
    while (1)// (input = readline("minishell$ ")) != NULL)
    {
      //system("leaks -q minishell");
      receive_signal(0);
      input = tcsetreadline(&content, 0);
    if (g_num == SIGINT)
		{
			content.exit_status = 1;
			g_num = 0;
		}
     if (input) 
        add_history(input);
      content.str_rl = input;
      if (!input)
      {
        printf("minishell$ exit\n");
        exit(1);
      }
      in = input_check(&content);//lexer for the parse
      if (in == 0)
          creating_parse(&content);
      executor(&content);
      free_struct_parse(&content);
     //check_command(&content);
      //printf("%s\n", input);
      //if (ft_strncmp(input, "exit", 4) == 0)
      //    exit(0);
     // if (ft_strncmp(input, "exit", 4) == 0)
       //   exit(0
      free(input);
    }
}
