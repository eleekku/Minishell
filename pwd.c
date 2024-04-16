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

void	change_directory(char *path)
{
	char	*pwd = get_pwd();
	char	*root;
	if (!path)
		path = get_root("minishell");
	int i = chdir(path);
	printf("%d\n", i);
	//char *pwd = get_pwd();
	printf("%s\n", pwd);
}

int	main(void)
{
	char *root;
	root = get_root("minishell");
	printf("%s\n", root);
	//change_directory("");
	/* char *pwd;
	pwd = get_pwd();
	printf("current dir is %s\n", pwd);
	free(pwd); */
}
