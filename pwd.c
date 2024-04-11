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
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1);
	if (!pwd)
		return (NULL);
	return (pwd);
}

change_directory(char *path)
{
	
}

int	main(void)
{
	char *pwd;
	pwd = get_pwd();
	printf("current dir is %s\n", pwd);
	free(pwd);
}
