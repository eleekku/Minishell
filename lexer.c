/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:53:06 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/03 16:49:50 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
char    *check_str_envp_redc(t_data *data, t_parse *parse, char *str, int i_token)
{
    int i;
    int len;

    i = 0;
    while (data->env[i])
    {
        len = ft_strchr(data->env[i], '=') - data->env[i];
        if (ft_strncmp(data->env[i], str + 1, len) == 0 && len + 1 == ft_strlen(str))
        {
            if (ft_strchr(str, ' ') == NULL)
            {   
                free (str);
                len = data->lexer_array[i_token].pos.len;
                str = ft_strdup(data->env[i] + len);
                return (str);
            } 
        }
        i++;
    }
    if (data->is_exp)
    {
        free (str);
        str = ft_strdup("");
    }
    return (str); 
}
char    *str_redc_dolar(t_data *data, t_parse *parse, int i_token)
{
    char *str;
    int len;

    len = data->lexer_array[i_token].pos.len;
    if (data->lexer_array[i_token].pos.start[0] == '$' && len == 1)
        return (ft_strdup("$"));
    if (data->lexer_array[i_token].pos.start[0] == '?')
    {
        str = ft_itoa(data->exit_status);
        //check for NULL
        return (str);
    }
    else
        str = ft_add_cmd_str(data->lexer_array[i_token].pos.start, len);
    //check for null;
    str = check_str_envp_redc(data, parse, str, i_token);
    return (str);
    //check for NULL
}
char    *make_recd_str(t_parse *parse, t_data *data, int i_token)
{
    char *tem1;
    char *temp2;
    char *rec;
    
    data->is_exp = 0;
    tem1 = ft_add_cmd_str(data->lexer_array[i_token].pos.start,
                        data->lexer_array[i_token].pos.len);
    //check for null
    i_token++;
    data->i_token = i_token;
    while (data->lexer_array[i_token].type != TOKEN_EOL 
            && data->lexer_array[i_token].type != TOKEN_PIPE)
    {
        if (data->lexer_array[i_token].type == TOKEN_DQUOTE_OPEN || data->lexer_array[i_token].type == TOKEN_S_QUOTE)
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
                break ;
            }
        }
        if(data->lexer_array[i_token].type == TOKEN_DOLAR)
        {
            temp2 = str_redc_dolar(data, parse, i_token);
            break ;
        }
        if(data->lexer_array[i_token].type == TOKEN_STR)
        {
            temp2 = ft_add_cmd_str(data->lexer_array[i_token].pos.start,
                        data->lexer_array[i_token].pos.len);
            break ;
        }
        i_token++;
    }
    rec = ft_strjoin(tem1, temp2);
    //malloc handle
    free(tem1);
    free(temp2);
    data->i_token = i_token;
    return (rec);
}

char *parse_dolar_dquate(t_data *data, int i_token)
{
    char *str;
    char **envp;
    int i;
    int len;

    envp = data->env;
    len = data->lexer_array[i_token].pos.len;
    str = ft_add_cmd_str(data->lexer_array[i_token].pos.start, len);
    i = 0;
    while (envp[i])
    {
        if (*str == '$' && ft_strlen(str) == 1)
            return(str);
        len = ft_strchr(envp[i], '=') - envp[i];
        if (ft_strncmp(envp[i], str + 1, len) == 0 && len + 1 == ft_strlen(str))
        {
            free(str);
            str = ft_strdup(envp[i] + data->lexer_array[i_token].pos.len);
            return (str);
        }
        i++;
    }
    free(str);
    str = ft_strdup("");
    return (str);
}

char    *check_dquote_str(t_data *data, int i_token)
{
    char    *temp2;
    int     len;

    len = data->lexer_array[i_token].pos.len;
    temp2 = NULL;
    if (data->lexer_array[i_token].type == TOKEN_DOLAR)
    {
        temp2 = parse_dolar_dquate(data, i_token);
        if (!temp2)
            return(NULL);
            
    }
    else
    {
        temp2 = ft_add_cmd_str(data->lexer_array[i_token].pos.start, len);
        if (!temp2)
            return(NULL);            
    }
    return (temp2);
}
bool    check_token_str_dquote(t_data *data, int i_token)
{
    if (data->lexer_array[i_token].type == TOKEN_DQUOTE_OPEN
        || data->lexer_array[i_token].type == TOKEN_STR 
        || data->lexer_array[i_token].type == TOKEN_S_QUOTE 
        || data->lexer_array[i_token].type == TOKEN_DOLAR)
    {
        return (true);
    }
    return (false);
}

char    **copy_realloc(char *str, char **new_ptr, int i, int size)
{
    int end;

    end = 0;
    while (++i < size - 1)
    {
        while (*str == ' ' && *str)
            str++;
		end = 0;
		while (str[end] != ' ' && str[end])
			end++;
		new_ptr[i] = ft_substr(str, 0, end);
        if (!new_ptr[i])
        {
            free_args(new_ptr);
            return (NULL);
        }
        str = str + end;
    }
    return (new_ptr);
}

char    **ft_realloc_char_array(char *str, t_parse *parse, t_data *data,
                                size_t new_size) 
{
    char **new_ptr;
    size_t copy_size;
    int i;
    int end;

    new_ptr = calloc(new_size + 1, sizeof(char *));
    if (new_ptr == NULL) 
        return NULL;
    if (data->i_str > 0)
    {
        i = -1;
        while (++i < data->i_str)
            new_ptr[i] = ft_strdup(parse[data->i_parse].cmd[i]);
    }
    free_args(parse[data->i_parse].cmd);
    end = 0;
    str = ft_strchr(str, '=') + 1;
    i = data->i_str - 1;
    new_ptr = copy_realloc(str, new_ptr, i, new_size);
    return (new_ptr);
}

int	ft_cont_str(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c && j == 0)
		{
			i++;
			j++;
		}
		if (*s == c && j != 0)
			j = 0;
		s++;
	}
	return (i);
}
bool   change_str_dolar(t_data *data, t_parse *parse, char *str, int i_token)
{
    int re_size;
    int len;
    
    len = data->lexer_array[i_token].pos.len;
    if (ft_strchr(str, ' ') == NULL)
    {
        parse[data->i_parse].cmd[data->i_str] = ft_strdup(str + len);
        return (true);
    }
    //check for null
    else
    {   
        re_size = ft_cont_str(ft_strchr(str, '=') + 1, ' ');
        parse[data->i_parse].cmd = ft_realloc_char_array(str, parse, data,
                                                        data->str + re_size);
        data->i_str += re_size - 1;
        return (true);
    }
    //check for null
    return (false);
} 

bool parse_dolar_envp(t_data *data, t_parse *parse, char *str, int i_token)//str + 1 is because str = $something
{
    int i;
    char **envp;
    size_t len;

    i = 0;
    envp = data->env;
    while (envp[i])
    {
        if (*str == '$' && ft_strlen(str) == 1)
        {   
            parse->cmd[data->i_str] = str;
            return (true);
        }
        len = ft_strchr(envp[i], '=') - envp[i];
        if (ft_strncmp(envp[i], str + 1, len) == 0 && len + 1 == ft_strlen(str))
        {
            free(str);
            if (change_str_dolar(data, parse, envp[i], i_token) == true)
                return (true);   
        }
        i++;
    }
    return (false);
}

int index_after_quate(t_data *data, int i)
{
    while (data->lexer_array[i].type != TOKEN_EOL
            && data->lexer_array[i].type != TOKEN_PIPE
            && is_redic(data, i) == false
            && data->lexer_array[i].type != TOKEN_SPACE)
        i++;
    return (i);
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

void    current_itoken(t_data *data)
{
    int i;

    i = data->i_token;
    while (data->lexer_array[i].type != TOKEN_EOL
            && data->lexer_array[i].type != TOKEN_PIPE)
        i++;
    data->i_token = i + 1;
}
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
        parse[i_parse].cmd = (char **)ft_calloc(data->str + 2, sizeof(char *));
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

    data->i_pipex = 1;
    if (check_error_token(data) != true)
        return ;
    parse = ft_calloc(data->i_pipex + 1, sizeof(t_parse));
    init_parse_struct(parse, data);
    add_data_to_parse(parse, data, data->i_pipex);
    data->parse = parse;
}
