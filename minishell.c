/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:22:09 by dzurita           #+#    #+#             */
/*   Updated: 2024/06/07 18:18:53 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_num;

void	exit_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	signals_crlt_d(void)
{
	printf("minishell$ exit\n");
	exit(g_num);
}

void	start_prompt(t_data *content)
{
	char	*input;
	int		in;

	while (1)
	{
		receive_signal(0);
		input = tcsetreadline(content, 0);
		if (g_num == SIGINT)
		{
			content->exit_status = 1;
			g_num = 0;
		}
		if (input)
			add_history(input);
		content->str_rl = input;
		if (!input)
			signals_crlt_d();
		in = input_check(content);
		if (in == 0)
			creating_parse(content);
		executor(content);
		free_struct_parse(content);
		if (input)
			free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	content;

	(void)av;
	content.exit_status = 127;
	content.here_doc_fd = -1;
	content.stdin_backup = dup(STDIN);
	content.stdout_backup = dup(STDOUT);
	if (ac != 1)
		exit_error("Invalid input\n");
	printf("Welcome to Minishell los pran...\n");
	create_envp(envp, &content);
	load_termios(&content);
	start_prompt(&content);
}
