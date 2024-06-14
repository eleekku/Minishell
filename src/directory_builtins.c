/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:49:04 by esalmela          #+#    #+#             */
/*   Updated: 2024/06/14 16:54:57 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "inc/minishell.h"

char	*get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_printf(2,
			"minishell$: error with getting current working directory\n");
	return (pwd);
}

void	print_pwd(t_data *cnt)
{
	char	*pwd;

	pwd = get_pwd();
	if (pwd)
		printf("%s\n", pwd);
	free (pwd);
	cnt->exit_status = 0;
}

void	cd_environment(t_data *content, char *variable)
{
	int		i;
	char	*arg;
	char	*pwd;

	i = 0;
	while (content->env[i] && ft_strncmp(variable, content->env[i], 7) != 0)
		i++;
	pwd = get_pwd();
	if (!content->env[i])
	{
		arg = safe_strjoin(variable, pwd, content);
		initialize_export(content, arg);
		free(arg);
	}
	else
	{
		free(content->env[i]);
		content->env[i] = safe_strjoin(variable, pwd, content);
	}
	free(pwd);
}

void	change_directory(char *path, t_data *content)
{
	int		return_value;
	char	*cwd;

	if (!path)
		path = content->root;
	cwd = get_pwd();
	if (!cwd)
	{
		path = content->root;
		chdir(path);
	}
	else
	{
		free (cwd);
		cd_environment(content, "OLDPWD=");
		return_value = chdir(path);
		if (return_value < 0)
		{
			ft_printf(2, "minishell$: cd: %s: ", path);
			perror("");
		}
		cd_environment(content, "PWD=");
		content->exit_status = return_value;
	}
}
