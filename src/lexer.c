/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:53:06 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/11 16:30:26 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

void	take_eol(t_char_iter *iter, t_token *token)
{
	token->type = TOKEN_EOL;
	token->pos.start = char_iter_cursor(iter);
	token->pos.len = 0;
}

void	lexer_tokenizer(t_data *data)
{
	t_char_iter	iter;
	t_token		*token;
	int			i;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
	{
		printf("minishell$: fatal error with malloc\n");
		exit(1);
	}
	iter = char_iter_constructor(data->str_rl, ft_strlen(data->str_rl));
	iter.d_flag = 0;
	i = 0;
	while (char_iter_cursor(&iter) != iter.end)
	{
		add_token(&token[i], &iter);
		i++;
		if (ft_realloc(&token, i + 1))
		{
			printf("minishell$: fatal error with malloc\n");
			exit(1);
		}
	}
	take_eol(&iter, &token[i]);
	data->lexer_array = token;
}

char	*check_str_envp_redc(t_data *data, char *str, int i_token)
{
	int	i;
	int	len;

	i = 0;
	while (data->env[i])
	{
		len = ft_strchr(data->env[i], '=') - data->env[i];
		if (ft_strncmp(data->env[i], str + 1, len) == 0
			&& len + 1 == (int)ft_strlen(str))
		{
			if (ft_strchr(data->env[i], ' '))
				return (str);
			free (str);
			len = data->lexer_array[i_token].pos.len;
			str = safe_strdup(data->env[i] + len, data);
			return (str);
		}
		i++;
	}
	if (data->is_exp)
	{
		free (str);
		str = safe_strdup("", data);
	}
	return (str);
}

int	just_pipes(char *str)
{
	if (str[0] == '\0')
		return (1);
	if (*str == '|' && ft_strlen(str) == 1)
	{
		printf("%s\n", "minishell: syntax error near unexpected token `|'");
		return (1);
	}
	if (*str == '|' && *str++ == '|')
	{
		printf("%s\n", "minishell: syntax error near unexpected token `||'");
		return (1);
	}
	return (0);
}

int	input_check(t_data *content)
{
	char	*str;
	int		error;

	str = content->str_rl;
	error = just_pipes(str);
	if (error)
		return (1);
	lexer_tokenizer(content);
	return (0);
}
