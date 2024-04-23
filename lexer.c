# include "minishelld.h"

/*void init_lexer(t_lexer* lexer, const char* input, size_t len) 
{
    lexer->start = 0;
    lexer->len = len;
    lexer->type = TOKEN_FIN;
}

// Advance lexer to the next token
void advance(t_lexer* lexer, const char* input) 
{
    while (lexer->start < lexer->len && isspace(input[lexer->start])) 
    {
        lexer->start++;
    }

    if (lexer->start >= lexer->len) 
    {
        lexer->type = TOKEN_FIN;
        return;
    }

    if (input[lexer->start] == '|') 
    {
        lexer->type = TOKEN_PIPEX;
        lexer->start++;
        return;
    }

    if (input[lexer->start] == '$') 
    {
        lexer->type = TOKEN_DOLAR;
        lexer->start++;
        return;
    }

    if (input[lexer->start] == '>') 
    {
        lexer->type = TOKEN_OUT_REDIRECT;
        lexer->start++;
        return;
    }

    if (input[lexer->start] == '<') 
    {
        lexer->type = TOKEN_IN_REDIRECT;
        lexer->start++;
        return;
    }

    if (input[lexer->start] == '\'') 
    {
        lexer->type = TOKEN_S_QUOTE;
        lexer->start++;
        return;
    }

    if (input[lexer->start] == '"') 
    {
        lexer->type = TOKEN_D_QUOTE;
        lexer->start++;
        return;
    }

    if (isalpha(input[lexer->start])) 
    {
        lexer->type = TOKEN_STR;
        while (isalpha(input[lexer->start]) || input[lexer->start] == '_') 
        {
            lexer->start++;
        }
        return;
    }

    if (input[lexer->start] == '!' || input[lexer->start] == '-' || input[lexer->start] == '/') 
    {
        lexer->type = TOKEN_COMMAND;
        lexer->start++;
        return;
    }
    lexer->type = TOKEN_ERROR;
    printf("Invalid character: %c\n", input[lexer->start]);
    //exit(1);
}*/

void    take_redir_in(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_IN_REDIRECT;
    token->pos.start = char_iter_cursor(iter);
    token->pos.len = 1;
    char_iter_next(iter);
}
void    take_redir_out(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_OUT_REDIRECT;
    token->pos.start = char_iter_cursor(iter);
    token->pos.len = 1;
    char_iter_next(iter);
}
void    take_s_quote(t_token *token, t_char_iter *iter)
{
    token->type = TOKEN_S_QUOTE;
    token->pos.start = char_iter_cursor(iter) + 1; // por que + 1;
    token->pos.len = 0;
    char_iter_next(iter);
    //calculate len of the string
    while (char_iter_cursor(iter) != iter->end && char_iter_cursor(iter) != "\'")
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

void    add_token(t_token *token, t_char_iter *iter)
{
    if (iter->start[0] == '<')
	    	take_redir_in(iter, token);
    else if (iter->start[0] == '>')
            take_redir_out(token, iter);
    else if (iter->start[0] == '\'')
            take_s_quote(token, iter);
}

void lexer_tokenizer(t_data *data) 
{
    t_char_iter iter;
    t_token *token;
    int i;
    int total_token;
    
    total_token = 100;
    token = ft_calloc(total_token, sizeof(t_token));
    if (!token)
        printf("Error Malloc token");
    iter = char_iter_constructor(data->str_rl, ft_strlen(data->str_rl));
    i = 0;
    while (char_iter_cursor(&iter) != iter.end)
    {
        add_token(&token[i], &iter);
        i++;
        if (i > 100)
            ft_realloc(&token, i + 1);
    }
    take_eof(&iter, &token[i]);
    data->lexer_array = token;
}

