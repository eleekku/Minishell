/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:49:04 by esalmela          #+#    #+#             */
/*   Updated: 2024/04/11 17:35:10 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1);
	if (!pwd)
		return (NULL);
	return (pwd);
}

char	*get_root(char *root)
{
	char	*pwd;
	char	*temp;
	int 	i;
	int		j;
	
	pwd = getcwd(NULL, 1);
	j = 0;
	i = ft_strlen(root);
	temp = ft_strnstr(pwd, root, ft_strlen(pwd));
	i += ft_strlen(pwd) - ft_strlen(temp);
	root = malloc(i + 1 * sizeof(char));
	if (!root)
		exit(1);
	while (j < i)
	{
		root[j] = pwd[j];
		j++;
	}
	free(pwd);
	root[j] = '\0';
	return (root);
}

int	change_directory(char *path, t_data *content)
{
	int	i;
	int return_value;

	char	*pwd = get_pwd();
	char	*root;
	if (!path)
		path = get_root("minishell");
	i = 0;
	while (content->env[i] && ft_strncmp("OLDPWD=", content->env[i], 7) != 0)
		i++;
	free(content->env[i]);
	content->env[i] = ft_strjoin("OLDPWD=", get_pwd());
	i = 0;
	return_value = chdir(path);
	while (content->env[i] && ft_strncmp("PWD=", content->env[i], 4) != 0)
		i++;
	free(content->env[i]);
	content->env[i] = ft_strjoin("PWD=", get_pwd());
	printf("%d\n", return_value);
	//char *pwd = get_pwd();
	printf("%s\n", pwd);
	return (return_value);
}

void  create_envp(char **env, t_data *content)
{
    char **envp;
    int i;
    int n;

    n = 0;
    while (env[n])
      n++;
    envp = (char **)malloc(sizeof(char *) * n + 1);
    if (!envp)
        perror("Error Mallloc created_envp");
    i = 0;
    while (i < n)
    {
      envp[i] = ft_strdup(env[i]);
      if (envp[i] == NULL)
          perror("Error Mallloc env_copy");
      i++;
    }
    envp[i] = NULL;
    content->env = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_data content;
  	create_envp(envp, &content);
	/* char *root;
	root = get_root("minishell");
	printf("%s\n", root); */
	//change_directory("");
	/* char *pwd;
	pwd = get_pwd();
	printf("current dir is %s\n", pwd);
	free(pwd); */
}
