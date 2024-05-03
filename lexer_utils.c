# include "minishell.h"

void    take_redir_in(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_IN_REDIRECT;
    token->pos.start = char_iter_cursor(iter);
    token->pos.len = 1;
    char_iter_next(iter);
}
void    take_redir_out(t_token *token, t_char_iter *iter)
{
    char	peek_next;

	peek_next = *(iter->start + 1);
	if (peek_next != *iter->end)
	{
		if (peek_next == '>')
		{
			take_redir_append(iter, token);
			return ;
		}
	}
    token->type = TOKEN_OUT_REDIRECT;
    token->pos.start = char_iter_cursor(iter);
    token->pos.len = 1;
    char_iter_next(iter);
}
void    take_s_quote(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_S_QUOTE;
    token->pos.start = char_iter_cursor(iter) + 1; // por que + 1; esto para mover el pointer y luego calcular el str
    token->pos.len = 0;
    char_iter_next(iter);
    //calculate len of the string
    while (char_iter_cursor(iter) != iter->end && char_iter_peek(iter) != '\'')
    {
        token->pos.len++;
        char_iter_next(iter);
    }
    if (char_iter_cursor(iter) == iter->end)
    {
        token->type = TOKEN_ERROR;
        token->pos.start--;
        token->pos.len = 1;
        return ;
    }
    else
        char_iter_next(iter);
}
void    take_space(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_SPACE;
    token->pos.start = char_iter_cursor(iter);
    token->pos.len = 0;
    while (char_iter_cursor(iter) != iter->end && (char_iter_peek(iter) == ' ' || char_iter_peek(iter) == '\t'))
    {
        char_iter_next(iter);
        token->pos.len++;
    }
}
void take_d_quote(t_token *token, t_char_iter *iter)
{
    token->pos.start = char_iter_cursor(iter);
    token->pos.len = 0;
    printf("d_flag1: %d\n", iter->d_flag);
    if (iter->d_flag % 2 == 0)
    {
        iter->d_flag += 1;
        token->type = TOKEN_DQUOTE_OPEN;
        token->pos.start++;
        printf("d_flag: %d\n", iter->d_flag);
        char_iter_next(iter);
        while (char_iter_cursor(iter) != iter->end && char_iter_peek(iter) != '"')
        {
            if (char_iter_peek(iter) == '$' && char_iter_peek_next(iter) != ' ' && char_iter_peek_next(iter) != '"')
                break ;
            token->pos.len++;
            char_iter_next(iter);
        }
        if (char_iter_cursor(iter) == iter->end)
            take_error(token, iter);
        return ;
    }
    token->type = TOKEN_DQUOTE_CLOSED;
    char_iter_next(iter);
    iter->d_flag += 1;
}
void take_exp(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_S_QUOTE;
    token->pos.start = char_iter_cursor(iter) + 1;
    token->pos.len = 0;
    char_iter_next(iter);
    while (char_iter_cursor(iter) != iter->end && char_iter_peek(iter) != 31)
    {
        char_iter_next(iter);
        token->pos.len++;
    }
    if (char_iter_cursor(iter) == iter->end || char_iter_peek(iter) == 31)
    {
        token->type = TOKEN_ERROR;
        token->pos.start--;
        token->pos.len = 1;
    }
    else
        char_iter_next(iter);
}
void    take_just_dollar(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_STR;
    token->pos.start = char_iter_cursor(iter);
    token->pos.len = 1;
    char_iter_next(iter);
    if (char_iter_peek(iter) == '?')
    {
        token->type = TOKEN_DOLAR;
        token->pos.start = char_iter_cursor(iter);
        char_iter_next(iter);
    }
}
void    take_dollar(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_DOLAR;
    token->pos.start = char_iter_cursor(iter);
    token->pos.len = 1;
    char_iter_next(iter);
    while (char_iter_cursor(iter) != iter->end 
            && !ft_strchr(DELIMITER, char_iter_peek(iter))
            && char_iter_peek(iter) != '/'
            && char_iter_peek(iter) != ':'
            && char_iter_peek(iter) != '@'
            && char_iter_peek(iter) != '=')
    {
        char_iter_next(iter);
        token->pos.len++;
    }
    if (char_iter_cursor(iter) == iter->end && iter->d_flag % 2 == 1)
    {
        take_error(token, iter);
        return ;
    }
}
void    take_pipe(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_PIPE;
    token->pos.start = char_iter_cursor(iter);
    token->pos.len = 1;
    char_iter_next(iter);
}
void    take_string(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_STR;
    token->pos.start = char_iter_cursor(iter);
    token->pos.len = 0;
    if (iter->d_flag % 2 == 0)
    {
        while (char_iter_cursor(iter) != iter->end && !ft_strchr(DELIMITER, char_iter_peek(iter)))
        {
            token->pos.len++;
            char_iter_next(iter);
        }
    }
    else
    {
        while (char_iter_cursor(iter) != iter->end && char_iter_peek(iter) != '"' && char_iter_peek(iter) != '$')
        {
            token->pos.len++;
            char_iter_next(iter);
        }
        if (char_iter_cursor(iter) == iter->end)
            take_error(token, iter);   
    }
}

void    add_token(t_token *token, t_char_iter *iter)
{
    if (iter->start[0] == '<' && iter->d_flag % 2 == 0)
	    take_redir_in(token, iter);
    else if (iter->start[0] == '>' && iter->d_flag % 2 == 0)
        take_redir_out(token, iter);
   else if (iter->start[0] == '\'' && iter->d_flag % 2 == 0 )
        take_s_quote(token, iter);
    else if ((iter->start[0] == ' ' || iter->start[0] == '\t') && iter->d_flag % 2 == 0)
        take_space(token, iter);
    else if (iter->start[0] == '"')
        take_d_quote(token, iter);
    else if (iter->start[0] == 31 && iter->d_flag % 2 == 0)
        take_exp(token, iter);
    else if (iter->start[0] == '$' && (iter->start[1] == '\0' || iter->start[1] == '?' || iter->start[1] == ' ' || iter->start[1] == '$' || iter->start[1] == '=' || ft_isdigit(iter->start[1])))
        take_just_dollar(token, iter);
    else if (iter->start[0] == '$' && iter->start[1] != '?' && iter->start[1] != '\0')
        take_dollar(token, iter);
    else if (iter->start[0] == '|' && iter->d_flag % 2 == 0)
        take_pipe(token, iter);
    else
        take_string(token, iter);
}
void    take_error(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_ERROR;
    token->pos.start = char_iter_cursor(iter);
    if (iter->d_flag % 2 == 1) //?
    {
        token->pos.start = char_find_dq(iter);
        *iter = char_iter_constructor(token->pos.start, ft_strlen(token->pos.start));
        token->pos.len = 1;
        return ;
    }
    printf("Error token %s\n", token->pos.start);
    token->pos.len = 0;
    while (char_iter_cursor(iter) != iter->end)
    {
        token->pos.len++;
        char_iter_next(iter);
    }  
}
void	take_redir_append(t_char_iter *iter, t_token *token)
{
	token->type = TOKEN_REDIR_APPEND;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 2;
	char_iter_next(iter);
	char_iter_next(iter);
}