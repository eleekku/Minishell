#include "minishell.h"

char	*check_flag(char *args, int *flag, int *n)
{
	int	i;

	i = 0;
	if (args[i] && (args[i] == '-')) // || args[i] == ' '))
	{
		i++;
		if (args[i] == 'n')
		{
			while (args[i] == 'n')
				i++;
			if (!args[i] || args[i] == ' ')
			*flag = 1;
		}				
	}
	if (*flag == 0 || args[i + 1])
		return (args);
	*n += 1;
	return (args + i);
}

void	echo(char **args)
{
	int i;
	int flag;
	int	n;

	i = 0;
	flag = 0;
	n = 0;
	while (args[++i])
	{
		args[i] = check_flag(args[i], &flag, &n);
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && n <= 0)
			ft_putchar_fd(' ', 1);
		n--;	
	}
	if (flag == 0)
		write(1, "\n", 1);
}
