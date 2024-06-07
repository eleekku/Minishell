#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <ctype.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> 
# include <termios.h>  

# define DELIMITER "|<>\"\'$ '\t'"
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define TRUE 1
# define FALSE 0

typedef int	t_bool;
extern int g_num;


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
    t_bool  outfile;
} t_parse;

typedef struct s_data
{
    struct termios	old;
	struct termios	new;
    char        **env;
    char        **exp;
    char        *str_rl;
    char        *root;
    int         str;
    int         irec;
    int         i_token;
    int         i_pipex;
    int         i_quate;
    int         i_str;
    int         i_parse;
    int         shlvl;
    int         exit_status;
    int         here_doc_fd;
    int         stdin_backup;
    int         stdout_backup;
    bool        is_exp;
    t_token     *lexer_array;
    t_parse     *parse;
    t_execute   *exec;
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
void    parse_dolar(t_data *data, t_parse *parse, int i_token, int i_parse);
int     index_after_quate(t_data *data, int i);
char    *make_str_dquote(t_data *data, int i_token, int i_quate);
void    parse_str(t_data *data, t_parse *parse, int i_parse);
bool    is_redic(t_data *data, int i);
bool    check_token_str_dquote(t_data *data, int i_token);
char    *check_dquote_str(t_data *data, int i_token);
bool    parse_dolar_envp(t_data *data, t_parse *parse, char *str, int i_token);
void    count_str_redic(t_data *data);
void    parse_redic(t_data *data, t_parse *parse, int i_parse);
void    current_itoken(t_data *data);
int	    ft_cont_str(const char *s, char c);
char    *parse_dolar_dquate(t_data *data, int i_token);
char    **ft_realloc_char_array(char *str, t_parse *parse, t_data *data, size_t new_size);
char    *str_redc_dolar(t_data *data, int i_token);
char    *check_str_envp_redc(t_data *data, char *str, int i_token);
void    free_struct_parse(t_data *data);
//bool    change_str_dolar(t_data *data, t_parse *parse, char *str, int i_token);

//signals
void	rl_replace_line(const char *text, int clear_undo);
void	receive_signal(int val);
char	*tcsetreadline(t_data *msh, int n);
void	load_termios(t_data *msh);

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
void        initialize_export(t_data *content, char *arg);
void        run_builtin(t_data *cnt);
void        echo(char **args);
char	    *get_pwd(void);
int         change_directory(char *path, t_data *content);
void        built_exit(char **args, t_data *cnt);
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
int         redirect(t_data	*cnt, int i);
void	    prepare_exit(t_data *content, int status);
void	    here_doc(char *limiter, t_data *cnt);

# endif
