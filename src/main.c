/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsurma <tsurma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:22:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/04/19 14:49:10 by tsurma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parsing.h"
#include "../includes/executing.h"

static char	**cpy_matrix(char **matrix);

// Handles Ctrl+C signal
void	sigint_handler(int sig)
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	sig = 1;
}

void	init_meta(char **envp, t_meta *meta)
/*
char **envp:	array of strings with all the environment variables
t_meta *meta:	empty meta struct

Initialize the meta struct. */
{
	meta->envp = cpy_matrix(envp);
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
	signal(SIGQUIT, SIG_IGN);

	(void)argc;
	(void)argv;
	cmnd_lst = NULL;
	meta.cmnd_lst = &cmnd_lst;
	init_meta(envp, &meta);
	while (1)
	{
		input = readline("\x1b[1;35mminishell :) \x1b[0m");
		if (input && *input)
		{
			add_history(input);
			if (parse(input, &meta) == 0)
				execute(&meta);
			free(input);
		}
		else if (!input)
			exit_error("exit", NULL, EXIT_SUCCESS, &meta);
	}
	rl_clear_history();
	return (0);
}

static char	**cpy_matrix(char **matrix)
{
	char	**ret;
	int		i;

	i = -1;
	while (matrix[++i])
		;
	ret = ft_calloc(sizeof(char *) + 1, i);
	if (!ret)
		return (NULL);
	i = -1;
	while (matrix[++i])
	{
		ret[i] = ft_strdup(matrix[i]);
		if (!ret[i])
		{
			i = -1;
			while (ret[i])
				free(ret[i]);
			free(ret);
			return (NULL);
		}
	}
	return (ret);
}
