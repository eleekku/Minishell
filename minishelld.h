#ifndef MINISHELLD_H
# define MINISHELLD_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_token{
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
} t_token;

typedef struct s_lexer
{
    int start;
    size_t len;
    t_token *type;
} t_lexer;

typedef struct s_data
{
    char **env;
    char *str_rl;
    t_lexer *lexerarra;
} t_data;

# endif