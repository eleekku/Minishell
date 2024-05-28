#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <stdbool.h>

# include <readline/readline.h>
# include <readline/history.h>
# define DELIMITER "|<>\"\'$ '\t'"
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define TRUE 1
# define FALSE 0

typedef int	t_bool;

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
    TOKEN_HEREDOC,
    TOKEN_IN_REDIRECT,
    TOKEN_OUT_REDIRECT,
    TOKEN_REDIR_APPEND,
    TOKEN_S_QUOTE,
    TOKEN_DQUOTE_OPEN,
    TOKEN_DQUOTE_CLOSED,
    TOKEN_ERROR,
    TOKEN_EOL,
} t_token_name;

typedef struct s_execute
{
    pid_t   *child;
    int     *pipesfd;
    int		fdtrack;
    int     currentfd;

} t_execute;

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

typedef struct s_parse
{
    char    **cmd;
    char    **rec_file;
} t_parse;

typedef struct s_data
{
    char        **env;
    char        **exp;
    char        *str_rl;
    char        *root;
    int         exit_status;
    int         str;
    int         irec;
    int         i_token;
    int         i_pipex;
    int         i_quate;
    t_execute   *exec;
    t_token     *lexer_array;
    t_parse     *parse;
} t_data;

//lexer
void    lexer_tokenizer(t_data* data);
void    take_error(t_token *token, t_char_iter *iter);
int	    ft_realloc(t_token **token, size_t size);
char	*char_find_dq(t_char_iter *self);
void	take_redir_append(t_char_iter *iter, t_token *token);
void    add_token(t_token *token, t_char_iter *iter);

//parse
void    creating_parse(t_data *data);
char	*ft_add_cmd_str(const char *src, int len);
char    *parse_dolar(t_data *data, int i_token);

//iter funtions
t_char_iter		char_iter_constructor(char *start, size_t	len);
char			*char_iter_cursor(t_char_iter *self);
char			char_iter_peek_next(t_char_iter *self);
char			*char_find_dq(t_char_iter *self);
char			char_iter_peek(t_char_iter *self);
char			char_iter_next(t_char_iter *self);

//execution
void	    free_args(char **args);
char	    *safe_strjoin(char const *s1, char const *s2);
void	    *safe_calloc(size_t nitems, size_t size);
char	    *safe_strdup(const char *src);
void        free_array(char **args);
char	    *get_root(void);
void        create_envp(char **env, t_data *content);
char        **export(char *arg, char **table);
int         unset_variable(t_data *content, char **args);
void        env(t_data *content);
void	    build_export(t_data *content);
void	    pre_export(t_data *cnt);
void        run_builtin(t_data *cnt);
void        echo(char **args);
char	    *get_pwd(void);
int         change_directory(char *path, t_data *content);
void        built_exit(char **args);
char        **add_space(char **table, int linel);
int         unset_variable(t_data *content, char **args);
void	    execution(t_data *cnt, int i, int fd);
void        executor(t_data *cnt);
void	    exec(char **cmd, char **env);
t_bool	    check_built_in(char **args);
void        piping_and_forking(t_data *cnt, int i);
t_execute	*init_exec_struct(int pipes);
char	    *get_path(char *cmd, char **envp, int *p);
void	    run_builtin_child(char **args, t_data *cnt);

# endif