#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>

# include <readline/readline.h>
# include <readline/history.h>
# define DELIMITER "|<>\"\'$ '\t'"

typedef struct s_split
{
	char	**str;
	size_t	start;
	size_t	end;
	size_t	len;
	size_t	i;
}	t_split;

typedef enum s_token_name
{
    TOKEN_PIPE,
    TOKEN_STR,
    TOKEN_DOLAR,
    TOKEN_SPACE,
    TOKEN_COMMAND,
    TOKEN_IN_REDIRECT,
    TOKEN_OUT_REDIRECT,
    TOKEN_REDIR_APPEND,
    TOKEN_S_QUOTE,
    TOKEN_DQUOTE_OPEN,
    TOKEN_DQUOTE_CLOSED,
    TOKEN_ERROR,
    TOKEN_EOL,
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
    int d_flag;
}	t_char_iter;

typedef struct s_data
{
    char **env;
    char **exp;
    char *str_rl;
    t_token *lexer_array;
} t_data;

//lexer
void    lexer_tokenizer(t_data* data);
void    take_error(t_token *token, t_char_iter *iter);
int	    ft_realloc(t_token **token, size_t size);
char	*char_find_dq(t_char_iter *self);
void	take_redir_append(t_char_iter *iter, t_token *token);

//iter funtions
t_char_iter		char_iter_constructor(char *start, size_t	len);
char			*char_iter_cursor(t_char_iter *self);
char			char_iter_peek_next(t_char_iter *self);
char			*char_find_dq(t_char_iter *self);
char			char_iter_peek(t_char_iter *self);
char			char_iter_next(t_char_iter *self);

//execution
void	free_args(char **args);
char	*safe_strjoin(char const *s1, char const *s2);
void	*safe_calloc(size_t nitems, size_t size);
void    create_envp(char **env, t_data *content);
int     export(char *arg, t_data *content);

# endif