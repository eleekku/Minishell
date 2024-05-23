#include "minishell.h"

char	*check_flag(char *args, int *flag, int *n)
{
	int	i;
	int temp;

	temp = 0;
	i = 0;
	if (args[i] && (args[i] == '-')) // || args[i] == ' '))
	{
		i++;
		if (args[i] == 'n')
		{
			while (args[i] == 'n')
				i++;
			//temp += (i - temp);
			if (!args[i] || args[i] == ' ')
			*flag = 1;
			/* if (args[i] == ' ')
			{
				temp += (i - temp);
				*flag = 1;
				i++;
			} */
		}				
	}
	if (*flag == 0 || args[i + 1])
		return (args);
	*n += 1;
	return (args + i); //temp);
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
/* void	echo(char *args)
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
} */

/* int main(int argc, char **argv)
{
	//argv[2] = "moiii\\nmmm";
	//argv[2][0] = 'm'
	//argv[2][1] = 'o'

	echo(argv[1]);
} */
