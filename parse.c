#include "minishell.h"

void    add_data_to_parse(t_parse *parse, t_data *data, int i_pipex)
{
    int i_parse;

    i_parse = 0;
    data->i_parse = i_parse;
    data->i_token = 0;
    data->i_str = 0;
    data->irec = 0;
    while (i_parse < i_pipex)
    {
        count_str_redic(data);
        parse[i_parse].cmd = (char **)ft_calloc(data->str + 1, sizeof(char *));
        //check for NULL
        parse[i_parse].rec_file = (char **)ft_calloc(data->irec + 1, sizeof(char *));
        //check for NULL
        parse_str(data, parse, i_parse);
        parse_redic(data, parse, i_parse);
        current_itoken(data);
        i_parse++;
        data->i_parse = i_parse;
    }
                                            // parte para imprimir mi parse struc
    int i = 0;
    int j = 0;
    int pi = i_pipex;
    while (i < pi)
    {
        printf("\nPARSE [%d]\n\n", i);
        j = 0;
        while (parse[i].cmd[j])
        {
            printf("cmd %s\n", parse[i].cmd[j]);
            j++;
        }
        j = 0;
        while (parse[i].rec_file[j])
        {
            printf("redc %s\n", parse[i].rec_file[j]);
            j++;
        }
        i++;
    }
    printf("\n");
}
bool    print_recd_error(t_data *data, int i)
{
    int red;
    
    red = 0;
    if (data->lexer_array[i].type == TOKEN_SPACE)
        i++;
    if (data->lexer_array[i].type == TOKEN_EOL)
    {
        printf("minishell: syntax error near unexpected token `newline'\n");
        return (true);
    }
    if (data->lexer_array[i].type != TOKEN_STR && data->lexer_array[i].type != TOKEN_DOLAR && data->lexer_array[i].type != TOKEN_DQUOTE_OPEN && data->lexer_array[i].type != TOKEN_S_QUOTE)
    {
        if (data->lexer_array[i].type == TOKEN_OUT_REDIRECT && data->lexer_array[i - 1].type == TOKEN_REDIR_APPEND)
            printf("minishell: syntax error near unexpected token >\n");
        if (data->lexer_array[i].type == TOKEN_IN_REDIRECT && data->lexer_array[i - 1].type == TOKEN_HEREDOC)
            printf("minishell: syntax error near unexpected token <\n");
        if (data->lexer_array[i].type == TOKEN_REDIR_APPEND && data->lexer_array[i - 1].type == TOKEN_REDIR_APPEND)
            printf("minishell: syntax error near unexpected token >>\n");
        if (data->lexer_array[i].type == TOKEN_HEREDOC && data->lexer_array[i - 1].type == TOKEN_HEREDOC)
            printf("minishell: syntax error near unexpected token <<\n");
        return (true);
    }
    return (false);
}
void    pipex_parse_error(t_data *data, int i)
{
    if (data->lexer_array[i].type == TOKEN_SPACE)
        i++;
    if (data->lexer_array[i].type == TOKEN_EOL)
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        data->i_pipex = -1;
    }
}

bool check_error_token(t_data *data)
{
    int i;

    i = 0;
    while (data->lexer_array[i].type != TOKEN_EOL) 
    {
        if (data->lexer_array[i].type == TOKEN_PIPE)
        {
            i++;
            data->i_pipex++;
            pipex_parse_error(data, i);
        }
        if (is_redic(data, i) == true)
        {
            i++;
            if (print_recd_error(data, i) == true)
                return (false);
        }
        if (data->lexer_array[i].type == TOKEN_ERROR)
            return  (false);
        if (data->i_pipex == -1)
            return (false);
        i++;
    }
    return (true); 
}

void    creating_parse(t_data *data)
{
    t_parse *parse;
    int     i;

    data->i_pipex = 1;
    if (check_error_token(data) != true)
        return ;
    parse = ft_calloc(data->i_pipex + 1, sizeof(t_parse));
    i = -1;
    while (++i < data->i_pipex)
    {
        parse[i].cmd = NULL;
        parse[i].rec_file = NULL;
    }
    //init_parse_struct(parse, data);
    add_data_to_parse(parse, data, data->i_pipex);
    data->parse = parse;
}