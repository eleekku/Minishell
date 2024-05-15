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
char    *make_recd_str(t_parse *parse, t_data *data, int i_token)
{
    char *tem1;
    char *temp2;
    char *rec;
    tem1 = ft_add_cmd_str(data->lexer_array[i_token].pos.start, data->lexer_array[i_token].pos.len);
    i_token++;
    if (data->lexer_array[i_token].type == TOKEN_SPACE)
        i_token++;
    temp2 = ft_add_cmd_str(data->lexer_array[i_token].pos.start, data->lexer_array[i_token].pos.len);
    //malloc handle
    rec = ft_strjoin(tem1, temp2);
    //malloc handle
    free(tem1);
    free(temp2);
    return (rec);
}
 bool    check_next_token(t_data *data, int i)
{
    if (data->lexer_array[i + 2].type == TOKEN_EOL)
        return (false);
    if (data->lexer_array[i].type == TOKEN_DQUOTE_OPEN  && data->lexer_array[i + 2].type != TOKEN_SPACE)
    {
        return (true);
    }
    if (data->lexer_array[i].type == TOKEN_S_QUOTE  && data->lexer_array[i + 2].type != TOKEN_SPACE)
    {
        return (true);
    }
    return (false);
}

char    *make_str_dquote(t_data *data, int i_token)
{
    char    *tem1;
    char    *temp2;
    char    *rec;
    tem1 = ft_add_cmd_str(data->lexer_array[i_token].pos.start, data->lexer_array[i_token].pos.len);
    i_token += 2;
    temp2 = ft_add_cmd_str(data->lexer_array[i_token].pos.start, data->lexer_array[i_token].pos.len);
    //malloc handle
    rec = ft_strjoin(tem1, temp2);
    //malloc handle
    free(tem1);
    free(temp2);
    return (rec);

}
char    *parse_dolar(t_data *data, int i_token)
{
    char *str;
    
    str = ft_add_cmd_str(data->lexer_array[i_token].pos.start, data->lexer_array[i_token].pos.len);
    return (str);
}

void    make_cmd_str(t_data *data, t_parse *parse)
{
    int i;
    int str;

    i = 0;
    str = 0;
    while (data->lexer_array[i].type != TOKEN_EOL)
    {
        if (data->lexer_array[i].type == TOKEN_DOLAR)
        {
            parse[0].cmd[str] = parse_dolar(data, i);
            str++;
        }
        if (data->lexer_array[i].type == TOKEN_STR || data->lexer_array[i].type == TOKEN_DQUOTE_OPEN || data->lexer_array[i].type == TOKEN_S_QUOTE)
        {   
            //continuar trabajando con las comillas
        //    if (check_next_token(data, i) == true)
        //    {
         //       parse[0].cmd[str] = make_str_dquote(data, i);
          //      i += 2;
         //   }
          //  else
           // {
                //printf("hola\n");
                parse[0].cmd[str] = ft_add_cmd_str(data->lexer_array[i].pos.start, data->lexer_array[i].pos.len);
           // }
            str++;
        }
        if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
            || data->lexer_array[i].type == TOKEN_OUT_REDIRECT
            || data->lexer_array[i].type == TOKEN_REDIR_APPEND)
        {
            i++;
            if (data->lexer_array[i].type == TOKEN_SPACE)
                i++;
        }
        i++;
    }
}
void    parse_redic(t_data *data, t_parse *parse)
{
    int i;
    int i_rec;

    i = 0;
    i_rec = 0;
    while (data->lexer_array[i].type != TOKEN_EOL)
    {
        if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
            || data->lexer_array[i].type == TOKEN_OUT_REDIRECT
            || data->lexer_array[i].type == TOKEN_REDIR_APPEND)
        {
            parse[0].rec_file[i_rec] = make_recd_str(parse, data, i);
            i_rec++;
        }
        i++;
    }
}
void    simple_cmd(t_parse *parse, t_data *data)
{
    int i;
    int str;
    int irec;

    i = 0;
    str = 0;
    irec = 0;
    while (data->lexer_array[i].type != TOKEN_EOL)
    {
        if (data->lexer_array[i].type == TOKEN_STR 
            || data->lexer_array[i].type == TOKEN_DQUOTE_OPEN 
            || data->lexer_array[i].type == TOKEN_S_QUOTE 
            || data->lexer_array[i].type == TOKEN_DOLAR)
            str++;
        if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
            || data->lexer_array[i].type == TOKEN_OUT_REDIRECT
            || data->lexer_array[i].type == TOKEN_REDIR_APPEND)
        {
            irec++;
            i++;
            if (data->lexer_array[i].type == TOKEN_SPACE)
                i++;
        }
        i++;
    }
    parse[0].cmd = (char **)ft_calloc(str + 1, sizeof(char *));
    //protect and free
    parse[0].rec_file = (char **)ft_calloc(irec + 1, sizeof(char *));
    //protect and free
    make_cmd_str(data, parse);
    parse_redic(data, parse);
    /*i = 0;
    while (parse[0].cmd[i])
    {
        printf("cmd %s\n", parse[0].cmd[i]);
        i++;
    }
    i = 0;
    while (parse[0].rec_file[i] != NULL)
    {
        printf("redc %s\n", parse[0].rec_file[i]);
        i++;
    }*/
    data->parse = parse;
}

void    creating_parse(t_data *data)
{
    int i;
    int pipex;
    int redic;
    t_parse *parse;

    i = 0;
    pipex = 1;
    redic = 0;
    while (data->lexer_array[i].type != TOKEN_EOL) 
    {
        if (data->lexer_array[i].type == TOKEN_PIPE)
            pipex++;
        if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
            || data->lexer_array[i].type == TOKEN_OUT_REDIRECT
            || data->lexer_array[i].type == TOKEN_REDIR_APPEND)
            redic++;
        i++;
    }
    parse = ft_calloc(pipex, sizeof(t_parse));
    i = 0;
    while (i < pipex)
    {
        parse[i].cmd = NULL;
        parse[i].rec_file = NULL;
        i++;
    }
    if (pipex == 1)
        simple_cmd(parse, data);
    //if (pipex > 1)
}
/*char *fill_cmd(t_data *data)
{
    char *tem;

    tem = (char *)ft_calloc(data->lexer_array->pos.len, sizeof(char));
    //tem = ft_strlcpy()
}*/
void    creating_command(t_data *data)
{
    //no pipes and redic
    int i;
    char **cmd;

    cmd = (char **)ft_calloc(2, sizeof(char *));
    if (!cmd)
        printf("Error malloc");
    //i = 0;
    /*while (data->lexer_array[i].type != TOKEN_EOL != TOKEN_EOL)
    {
        if (data->lexer_array[i].type == TOKEN_STR)
            ft_strdup()
    }*/
    //data->parse[0].cmd 
}
/*void    creating_str_files(t_data *data)
{

}*/
