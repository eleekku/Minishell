# include "minishell.h"

void	take_eol(t_char_iter *iter, t_token *token)
{
	token->type = TOKEN_EOL;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 0;
}

void lexer_tokenizer(t_data *data) 
{
    t_char_iter iter;
    t_token *token;
    int i;
    
    token = ft_calloc(1, sizeof(t_token));
    if (!token)
        printf("Error Malloc token");
    iter = char_iter_constructor(data->str_rl, ft_strlen(data->str_rl));
    iter.d_flag = 0;
    i = 0;
    while (char_iter_cursor(&iter) != iter.end)
    {   
        add_token(&token[i], &iter);
        i++;
        if (ft_realloc(&token, i + 1))
            printf("Error Malloc token");
    }
    take_eol(&iter, &token[i]);
    data->lexer_array = token;
}

bool    is_redic(t_data *data)
{
    if (data->lexer_array->type == TOKEN_IN_REDIRECT
        || data->lexer_array->type == TOKEN_OUT_REDIRECT
        || data->lexer_array->type == TOKEN_REDIR_APPEND)
        return (true);
    return (false);
}
void    creating_parse(t_data *data)
{
    int i;
    int pipes;
    int redic;
    t_parse *parse;

    i = 0;
    pipes = 1;
    redic = 0;
    while (data->lexer_array[i].type != TOKEN_EOL) 
    {
        if (data->lexer_array[i].type == TOKEN_PIPE)
            pipes++;
        if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
            || data->lexer_array[i].type == TOKEN_OUT_REDIRECT
            || data->lexer_array[i].type == TOKEN_REDIR_APPEND)
            redic++;
        i++;
    }
    parse = ft_calloc(pipes, sizeof(t_parse));
    parse = data->parse;
    printf("p: %d\n r: %d\n", pipes, redic);
    if (pipes == 1 && redic == 0)
        creating_command(data);
    /*if (data->lexer_array[i].type == TOKEN_PIPE)
        //create new struct;
    if (data->lexer_array[i].type == TOKEN_IN_REDIRECT )
    {
        
    }*/
    
}
char *fill_cmd(t_data *data)
{
    char *tem;

    tem = (char *)ft_calloc(data->lexer_array->pos.len, sizeof(char));
    //tem = ft_strlcpy()
}
void    creating_command(t_data *data)
{
    //no pipes and redic
    int i;
    char **cmd;

    cmd = (char **)ft_calloc(2, sizeof(char *));
    if (!cmd)
        printf("Error malloc");
    i = 0;
    while (data->lexer_array[i].type != TOKEN_EOL != TOKEN_EOL)
    {
        if (data->lexer_array[i].type == TOKEN_STR)
            ft_strdup()
    }


    data->parse[0].cmd 
}
void    creating_str_files(t_data *data)
{

}*/
