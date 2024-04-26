# include "minishelld.h"

void    take_error(t_token *token, t_char_iter *iter, int *d_flag)
{
    token->type = TOKEN_ERROR;
    token->pos.start = char_iter_cursor(iter);
    if (*d_flag % 2 == 1) //?
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
