# include "minishelld.h"

int input_check(t_data *content)
{

}
void exit_error(char *str)
{
  printf("%s\n", str);
  exit(1);
}

int main(int ac, char **av, char **envp) 
{
  char* input;
  t_data content;

  if (ac == 0 || ac > 1)
      exit_error("Invalid input\n");
  printf("Welcome to Minishell los pran...\n");
  content.env = envp;
  while ((input = readline("minishell$ ")) != NULL) 
  {
    if (strlen(input) > 0) 
      add_history(input);
    content.str_rl = &input;
    input_check(&content);
    printf("%s\n", input);
    free(input);
  }
  return (0);
}
