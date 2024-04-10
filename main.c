/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:22:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/10 11:38:02 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/parsing.h"
#include "includes/executing.h"

void sigint_handler(int sig) {
	// Print a message indicating that Ctrl+C was pressed
	printf("\nCtrl+C pressed. Enter a new command:\n");
	sig = 1;
}

void sigquit_handler(int sig) {
	sig = 1;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*cmnd_lst;
	t_meta	meta;

	// Register the signal handlers for SIGINT (Ctrl+C), EOF (Ctrl+D), and SIGQUIT (Ctrl+\)
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);

	(void)argc;
	(void)argv;
	cmnd_lst = NULL;
	meta.envp = envp;
	meta.exit_code = 0;
	meta.cmnd_lst = &cmnd_lst;
	while(1)
	{
		input = readline("\x1b[1;35mminishell :) \x1b[0m");
		if (input && *input)
		{
			add_history(input);
			if (parse(input, &meta))
			{
				meta.cmnd_lst = &cmnd_lst;
				execute(&cmnd_lst, &meta);
			}
			free(input);
		}
		else if (!input)
			exit_error("exit", NULL, EXIT_SUCCESS, &meta);
	}
	rl_clear_history();
	return (0);
}
