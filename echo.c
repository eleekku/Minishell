#include "minishell.h"

void	echo(char *flag, char *args)
{
	int i;

	i = -1;
	if (flag[1] == 'E' && args)
		ft_putstr_fd(args, 1);
	else if (args)
		ft_putstr_fd(args, 1);
	if ((flag && flag[1] != 'n') || (!flag))
		write(1, "\n", 1);
}

int main(int argc, char **argv)
{
	argv[2] = "moiii '\\n'mmm";
	echo(argv[1], argv[2]);
}