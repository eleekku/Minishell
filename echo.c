#include "minishell.h"

char	*check_flag(char *args, int *flag)
{
	int	i;
	int temp;

	*flag = 0;
	temp = 0;
	i = 0;
	while (args[i] && (args[i] == '-' || args[i] == ' '))
	{
		i++;
		if (args[i] == 'n')
		{
			while (args[i] == 'n')
				i++;
			if (args[i] == ' ')
			{
				temp += (i - temp);
				*flag = 1;
				i++;
			}
		}				
	}
	if (*flag == 0)
		return (args);
	return (args + temp);
}

void	echo(char *args)
{
	int i;
	int	sin_quotations;
	int	dup_quotations;
	int	flag;

	i = -1;
	sin_quotations = 0;
	dup_quotations = 0;
	args = check_flag(args, &flag);
	while (args[++i])
	{
		if (args[i] == '\"')
			dup_quotations += 1;
		if (args[i] == '\'')
			sin_quotations += 1;
		if (args[i] == ' ' && dup_quotations % 2 == 0 && sin_quotations % 2 == 0)
		{
			while (args[i] == ' ')
				i++;
			ft_putchar_fd(' ', 1);
		}
		ft_putchar_fd(args[i], 1);
	}
	if (flag == 0)
		write(1, "\n", 1);
}

int main(int argc, char **argv)
{
	//argv[2] = "moiii\\nmmm";
	//argv[2][0] = 'm'
	//argv[2][1] = 'o'

	echo(argv[1]);
}
