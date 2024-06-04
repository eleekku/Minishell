#include  "minishell.h"

static  char    *make_recd_str_utils(t_parse *parse, t_data *data,
                 char *temp2, int i_token)
{
    if (data->lexer_array[i_token].type == TOKEN_DQUOTE_OPEN
        || data->lexer_array[i_token].type == TOKEN_S_QUOTE)
    {
        if (data->lexer_array[i_token + 1].type == TOKEN_DQUOTE_CLOSED
            && data->lexer_array[i_token].pos.len == 0)
        {
            data->is_exp = 1;
            i_token++;
        }
        else 
        {
            temp2 = make_str_dquote(data, i_token, index_after_quate(data, i_token));
            i_token = index_after_quate(data, i_token) - 1;
        }
    }
    if(data->lexer_array[i_token].type == TOKEN_DOLAR)
        temp2 = str_redc_dolar(data, parse, i_token);
    if(data->lexer_array[i_token].type == TOKEN_STR)
        temp2 = ft_add_cmd_str(data->lexer_array[i_token].pos.start,
                    data->lexer_array[i_token].pos.len);
    data->i_token = i_token;
    return(temp2);
}

char    *make_recd_str(t_parse *parse, t_data *data, int i_token)
{
    char *tem1;
    char *temp2;
    char *rec;
    
    temp2 = NULL;
    data->is_exp = 0;
    tem1 = ft_add_cmd_str(data->lexer_array[i_token].pos.start,
                        data->lexer_array[i_token].pos.len);
    //check for null
    i_token++;
    if (data->lexer_array[i_token].type == TOKEN_SPACE)
        i_token++;
    temp2 = make_recd_str_utils(parse, data,  temp2, i_token);
    rec = ft_strjoin(tem1, temp2);
    //malloc handle
    free(tem1);
    free(temp2);
    return (rec);
}

void    parse_redic(t_data *data, t_parse *parse, int i_parse)
{
    int i;
    int i_rec;

    i = data->i_token;
    i_rec = 0;
    while (data->lexer_array[i].type != TOKEN_EOL 
            && data->lexer_array[i].type != TOKEN_PIPE)
    {
        if (data->lexer_array[i].type == TOKEN_IN_REDIRECT
            || data->lexer_array[i].type == TOKEN_OUT_REDIRECT
            || data->lexer_array[i].type == TOKEN_REDIR_APPEND
            || data->lexer_array[i].type == TOKEN_HEREDOC)
        {
            parse[i_parse].rec_file[i_rec] = make_recd_str(parse, data, i);
            /*if (parse[i_parse].rec_file[i_rec] + 1 == '\0')
            {
                printf("bash: $ok: ambiguous redirect");
            }*/
            i_rec++;
            i = data->i_token;
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
    while (data->lexer_array[i].type != TOKEN_EOL
            && data->lexer_array[i].type != TOKEN_PIPE)
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