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

bool    is_redic(t_data *data, int i)
{
    if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
        || data->lexer_array[i].type == TOKEN_OUT_REDIRECT
        || data->lexer_array[i].type == TOKEN_REDIR_APPEND
        || data->lexer_array[i].type == TOKEN_HEREDOC)
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
    {
        i_token++;
        if (data->lexer_array[i_token].type == TOKEN_EOL)
            return (NULL);
    }
    if (data->lexer_array[i_token].type == TOKEN_EOL)
        return (NULL);
    temp2 = ft_add_cmd_str(data->lexer_array[i_token].pos.start, data->lexer_array[i_token].pos.len);
    //malloc handle
    rec = ft_strjoin(tem1, temp2);
    //malloc handle
    free(tem1);
    free(temp2);
    return (rec);
}
bool    check_next_token(t_data *data, int i) //this check is to create the str when there are quates
{
    if (data->lexer_array[i + 2].type == TOKEN_EOL)
        return (false);
    if (data->lexer_array[i].type == TOKEN_DQUOTE_OPEN  && data->lexer_array[i + 2].type != TOKEN_SPACE)
        return (true);
    if (data->lexer_array[i].type == TOKEN_S_QUOTE  && data->lexer_array[i + 2].type != TOKEN_SPACE)
        return (true);
    return (false);
}

char    *make_str_dquote(t_data *data, int i_token, int i_quate)
{
    char    *temp2;
    char    *rec;
    
    rec = NULL;
    temp2 =  NULL;
    while (i_quate > i_token)//i_quate es el punto final del str que va a crear.
    {
        if (data->lexer_array[i_token].type == TOKEN_DQUOTE_OPEN || data->lexer_array[i_token].type == TOKEN_STR || data->lexer_array[i_token].type == TOKEN_S_QUOTE || data->lexer_array[i_token].type == TOKEN_DOLAR)
        {
            if (data->lexer_array[i_token].type == TOKEN_DOLAR)
            {
                temp2 = parse_dolar(data, i_token);
                //printf("dolar : %s\n.", temp2);
                if (!temp2)
                {
                    if(rec)
                        free(rec);
                    return(NULL);
                }
            }//malloc handle
            else
            {
                temp2 = ft_add_cmd_str(data->lexer_array[i_token].pos.start, data->lexer_array[i_token].pos.len);
                if (!temp2)
                {
                    if(rec)
                        free(rec);
                    return(NULL);
                }
            }//malloc handle
            rec = ft_strjoingnl(rec, temp2);
            free(temp2);
        }
        i_token++;
    }
    return (rec);
}
char    *parse_dolar(t_data *data, int i_token)
{
    char *str;
    char **envp;
    int i;

    envp = data->env;
    str = ft_add_cmd_str(data->lexer_array[i_token].pos.start, data->lexer_array[i_token].pos.len);
    i = 0;
    while (envp[i])
    {
        if (*str == '$' && ft_strlen(str) == 1)
        {
            str = ft_strdup("$");
            //protect malloc
            return(str);
        }
        if (ft_strncmp(envp[i], str + 1, data->lexer_array[i_token].pos.len - 1) == 0)
        {
            free(str);
            str = ft_strdup(envp[i] + data->lexer_array[i_token].pos.len);
            //check for null
            return (str);
        }
        i++;
    }
    free(str);
    str = ft_strdup("");
    return (str);
}
int index_after_quate(t_data *data, int i)
{
    while (data->lexer_array[i].type != TOKEN_EOL && data->lexer_array[i].type != TOKEN_PIPE && is_redic(data, i) == false && data->lexer_array[i].type != TOKEN_SPACE)
        i++;
    return (i);
}
void    parse_str(t_data *data, t_parse *parse, int i_parse)
{
    int i;
    int str;
    char *temp;

    i = data->i_token;
    str = 0;
    while (data->lexer_array[i].type != TOKEN_EOL && data->lexer_array[i].type != TOKEN_PIPE)
    {
        if (data->lexer_array[i].type == TOKEN_DOLAR)
        {
            parse[i_parse].cmd[str] = parse_dolar(data, i);
            str++;
        }
        if (data->lexer_array[i].type == TOKEN_DQUOTE_OPEN || data->lexer_array[i].type == TOKEN_S_QUOTE)
        {
            parse[i_parse].cmd[str] = make_str_dquote(data, i, index_after_quate(data, i));
            i = index_after_quate(data, i) - 1;
            str++;
        }
        if  (data->lexer_array[i].type == TOKEN_STR)
        {
            parse[i_parse].cmd[str] = ft_add_cmd_str(data->lexer_array[i].pos.start, data->lexer_array[i].pos.len);
            if (data->lexer_array[i + 1].type == TOKEN_DQUOTE_OPEN || data->lexer_array[i + 1].type == TOKEN_S_QUOTE)
            {
                i++;
                temp = make_str_dquote(data, i, index_after_quate(data, i));
                parse[i_parse].cmd[str] = ft_strjoingnl(parse[i_parse].cmd[str], temp);
                free(temp);
                i = index_after_quate(data, i) - 1;
            }
            str++;
        }
        if (is_redic(data, i) == true)
        {
            i++;
            if (data->lexer_array[i].type == TOKEN_SPACE)
                i++;
        }
        i++;
    }
}
void    parse_redic(t_data *data, t_parse *parse, int i_parse)
{
    int i;
    int i_rec;

    i = data->i_token;
    i_rec = 0;
    while (data->lexer_array[i].type != TOKEN_EOL && data->lexer_array[i].type != TOKEN_PIPE)
    {
        if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
            || data->lexer_array[i].type == TOKEN_OUT_REDIRECT
            || data->lexer_array[i].type == TOKEN_REDIR_APPEND
            || data->lexer_array[i].type == TOKEN_HEREDOC)
        {
            parse[i_parse].rec_file[i_rec] = make_recd_str(parse, data, i);
            i_rec++;
        }
        i++;
    }
}

void    count_str_redic(t_data *data)
{
    int i;

    i = data->i_token;
    data->str = 0;
    data->irec = 0;
    while (data->lexer_array[i].type != TOKEN_EOL && data->lexer_array[i].type != TOKEN_PIPE)
    {
        if (data->lexer_array[i].type == TOKEN_STR 
            || data->lexer_array[i].type == TOKEN_DQUOTE_OPEN 
            || data->lexer_array[i].type == TOKEN_S_QUOTE 
            || data->lexer_array[i].type == TOKEN_DOLAR)
            data->str++;
        if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
            || data->lexer_array[i].type == TOKEN_OUT_REDIRECT
            || data->lexer_array[i].type == TOKEN_REDIR_APPEND
            || data->lexer_array[i].type == TOKEN_HEREDOC)
        {
            data->irec++;
            i++;
            if (data->lexer_array[i].type == TOKEN_SPACE)
                i++;
        }
        i++;
    }
}
void    current_itoken(t_data *data)
{
    int i;

    i = data->i_token;
    while (data->lexer_array[i].type != TOKEN_EOL && data->lexer_array[i].type != TOKEN_PIPE)
        i++;
    data->i_token = i + 1;
}
void    simple_test(t_parse *parse, t_data *data, int i_pipex)
{
    int i_parse;

    i_parse = 0;
    data->i_token = 0;
    while (i_parse < i_pipex)
    {
        count_str_redic(data);
        parse[i_parse].cmd = (char **)ft_calloc(data->str + 1, sizeof(char *));
        //protect and free
        parse[i_parse].rec_file = (char **)ft_calloc(data->irec + 1, sizeof(char *));
        //protect and free
        parse_str(data, parse, i_parse);
        parse_redic(data, parse, i_parse);
        current_itoken(data);
        i_parse++;
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
void    init_parse_struct(t_parse *parse, t_data *data)
{
    int i;

    i = 0;
    while (i < data->i_pipex)
    {
        parse[i].cmd = NULL;
        parse[i].rec_file = NULL;
        i++;
    }
}

void    creating_parse(t_data *data)
{
    int i;
    t_parse *parse;

    i = 0;
    data->i_pipex = 1;
    while (data->lexer_array[i].type != TOKEN_EOL) 
    {
        if (data->lexer_array[i].type == TOKEN_PIPE)
            data->i_pipex++;
        if (is_redic(data, i) == true)
        {
            if (data->lexer_array[i + 1].type == TOKEN_EOL)
            {
                printf("minishell: syntax error near unexpected token `newline'\n");
                return ;
            }
        }
        if (data->lexer_array[i].type == TOKEN_ERROR)
            return ;
        i++;
    }
    parse = ft_calloc(data->i_pipex + 1, sizeof(t_parse));
    init_parse_struct(parse, data);
    simple_test(parse, data, data->i_pipex);
}
