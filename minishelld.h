#ifndef MINISHELLD_H
# define MINISHELLD_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>

# include <readline/readline.h>
# include <readline/history.h>

//# define total_token 100;

typedef enum {
    TOKEN_PIPEX,
    TOKEN_STR,
    TOKEN_DOLAR,
    TOKEN_COMMAND,
    TOKEN_IN_REDIRECT,
    TOKEN_OUT_REDIRECT,
    TOKEN_S_QUOTE,
    TOKEN_D_QUOTE,
    TOKEN_ERROR,
    TOKEN_FIN
} t_token_name;

typedef struct s_lexer
{
    char *start;
    size_t len;
} t_lexer;

typedef struct s_token
{
    t_token_name    type;
    t_lexer         pos;
} t_token;

typedef struct s_char_iter
{
	char	*start;
	char	*end;
}	t_char_iter;

typedef struct s_data
{
    char **env;
    char *str_rl;
    t_token *lexer_array;
} t_data;

void lexer_tokenizer(t_data* data);

//iter funtions
t_char_iter		char_iter_constructor(char *start, size_t	len);
char			*char_iter_cursor(t_char_iter *self);
char			char_iter_peek_next(t_char_iter *self);
char			*char_find_dq(t_char_iter *self);
char			char_iter_peek(t_char_iter *self);
char			char_iter_next(t_char_iter *self);

# endif