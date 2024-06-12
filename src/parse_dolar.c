/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dolar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:58:04 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/11 13:52:14 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static void	exp_str_dolar(t_data *data, t_parse *parse, int re_size, char *str)
{
	int	end;

	while (data->i_str < re_size)
	{
		while (*str == ' ' && *str)
			str++;
		end = 0;
		while (str[end] != ' ' && str[end])
			end++;
		parse[data->i_parse].cmd[data->i_str] = safe_substr(str, 0, end, data);
		str = str + end;
		data->i_str++;
	}
}

bool	change_str_dolar(t_data *data, t_parse *parse, char *str, int i_token)
{
	int	re_size;
	int	len;

	len = data->lexer_array[i_token].pos.len;
	if (ft_strchr(str, ' ') == NULL)
	{
		parse[data->i_parse].cmd[data->i_str] = safe_strdup(str + len, data);
		return (true);
	}
	else
	{
		re_size = ft_cont_str(ft_strchr(str, '=') + 1, ' ') + data->i_str;
		str = ft_strchr(str, '=') + 1;
		exp_str_dolar(data, parse, re_size, str);
		return (true);
	}
	return (false);
}

char	*str_redc_dolar(t_data *data, int i_token)
{
	char	*str;
	int		len;

	len = data->lexer_array[i_token].pos.len;
	if (data->lexer_array[i_token].pos.start[0] == '$' && len == 1)
		return (safe_strdup("$", data));
	if (data->lexer_array[i_token].pos.start[0] == '?')
	{
		str = ft_itoa(data->exit_status);
		if (!str)
		{
			ft_printf(2, "minishell$: fatal error with malloc\n");
			prepare_exit(data, 1);
		}
		return (str);
	}
	else
		str = ft_add_cmd_str(data->lexer_array[i_token].pos.start, len, data);
	str = check_str_envp_redc(data, str, i_token);
	return (str);
}

char	*parse_dolar_dquate(t_data *ctn, int i_token)
{
	char	*str;
	char	**envp;
	int		i;
	int		len;

	envp = ctn->env;
	len = ctn->lexer_array[i_token].pos.len;
	str = ft_add_cmd_str(ctn->lexer_array[i_token].pos.start, len, ctn);
	i = -1;
	while (envp[++i])
	{
		if (*str == '$' && ft_strlen(str) == 1)
			return (str);
		len = ft_strchr(envp[i], '=') - envp[i];
		if (ft_strncmp(envp[i], str + 1, len) == 0
			&& len + 1 == (int)ft_strlen(str))
		{
			free(str);
			str = safe_strdup(envp[i] + ctn->lexer_array[i_token].pos.len, ctn);
			return (str);
		}
	}
	free(str);
	str = safe_strdup("", ctn);
	return (str);
}

bool	parse_dolar_envp(t_data *data, t_parse *parse, char *str, int i_token)
{
	int		i;
	char	**envp;
	size_t	len;

	i = 0;
	envp = data->env;
	while (envp[i])
	{
		if (*str == '$' && ft_strlen(str) == 1)
		{
			parse->cmd[data->i_str] = str;
			return (true);
		}
		len = ft_strchr(envp[i], '=') - envp[i];
		if (ft_strncmp(envp[i], str + 1, len) == 0 && len + 1 == ft_strlen(str))
		{
			free(str);
			if (change_str_dolar(data, parse, envp[i], i_token) == true)
				return (true);
		}
		i++;
	}
	return (false);
}
