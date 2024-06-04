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

char	*get_root(void)
{
	char	*pwd;
	char	*temp;
	int 	i;
	
	i = -1;
	pwd = getcwd(NULL, 1);
	int len = ft_strlen(pwd);
	temp = safe_calloc(len + 1, sizeof(char));
	while (pwd[++i])
		temp[i] = pwd[i];
	free(pwd);
	return (temp);
}

int	change_directory(char *path, t_data *content)
{
	int	i;
	int return_value;

	if (!path)
		path = content->root;
	i = 0;
	while (content->env[i] && ft_strncmp("OLDPWD=", content->env[i], 7) != 0)
		i++;
	if (!content->env[i])
		export(safe_strjoin("OLDPWD=", get_pwd()), content->env);
	free(content->env[i]);
	content->env[i] = safe_strjoin("OLDPWD=", get_pwd());
	i = 0;
	return_value = chdir(path);
	while (content->env[i] && ft_strncmp("PWD=", content->env[i], 4) != 0)
		i++;
	free(content->env[i]);
	content->env[i] = safe_strjoin("PWD=", get_pwd());
	//char *pwd = get_pwd();
	return (return_value);
}
/* 
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
	change_directory("/", &content);
	char *root;
	root = get_root("minishell");
	printf("%s\n", root); 
	//change_directory("");
	 char *pwd;
	pwd = get_pwd();
	printf("current dir is %s\n", pwd);
	free(pwd); 
} */
