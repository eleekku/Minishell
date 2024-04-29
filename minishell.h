/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:56:05 by esalmela          #+#    #+#             */
/*   Updated: 2024/04/11 17:36:14 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>

typedef struct s_split
{
	char	**str;
	size_t	start;
	size_t	end;
	size_t	len;
	size_t	i;
}	t_split;

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
    char **exp;
    char *str_rl;
    t_lexer *lexerarra;
} t_data;

void	free_args(char **args);
char	*safe_strjoin(char const *s1, char const *s2);
void	*safe_calloc(size_t nitems, size_t size);

#endif
