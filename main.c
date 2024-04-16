/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:22:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/16 15:35:35 by evan-ite         ###   ########.fr       */
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

void	init_meta(char **envp, t_meta *meta)
/*
char **envp:	array of strings with all the environment variables
t_meta *meta:	empty meta struct

Initialize the meta struct. */
{
	meta->envp = envp;
	meta->exit_code = 0;
	meta->n_cmnds = 0;
	meta->pid = NULL;
	meta->pipe = NULL;
}

int	main(int argc, char **argv, char **envp)
/*
int argc:		number of arguments user put at start of the program
char **argv:	array of strings with the input the user put at start of the program
char **envp:	array of strings with all the environment variables

Starts Minishell by creating an infinite while loop,
keeps prompting the user for input until user exits the program. */
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
	meta.cmnd_lst = &cmnd_lst;
	init_meta(envp, &meta);
	while(1)
	{
		input = readline("\x1b[1;35mminishell :) \x1b[0m");
		if (input && *input)
		{
			add_history(input);
			if (!parse(input, &meta))
				execute(&meta);
			free(input);
		}
		else if (!input)
			exit_error("exit", NULL, EXIT_SUCCESS, &meta);
	}
	rl_clear_history();
	return (0);
}
