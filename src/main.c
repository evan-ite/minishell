/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobias <tobias@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:22:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/01 16:10:32 by tobias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executing.h"
#include "../includes/parsing.h"

static char **cpy_matrix(char **matrix);

int	g_sig = 0;

/*
Executes when the ctrl+c signal is send.
writes a new line and reinitialises it to display the prompt*/
void sigint_handler(int sig)
{
	g_sig = sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
char **envp:	An editable copy of the environment variables.
t_meta *meta:	empty meta struct

Initialize the meta struct. */
void init_meta(t_meta *meta)
{
	meta->envp = cpy_matrix(__environ);
	meta->exit_code = 0;
	meta->n_cmnds = 0;
	meta->pid = NULL;
	meta->pipe = NULL;
}

/*
Registers the Signals for SIGINT (ctrl+c) and SIGQUIT (ctrl+d) which is ignored
and runs by itself. ctrl+/ is not supposed to do anything.
Starts Minishell by creating an infinite while loop,
keeps prompting the user for input until user exits the program. */
int main(void)
{
	char	*input;
	t_list	*cmnd_lst;
	t_meta	meta;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	cmnd_lst = NULL;
	meta.cmnd_lst = &cmnd_lst;
	init_meta(&meta);
	while (1)
	{
		g_sig = 0;
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

/*
Simple function that takes a char** and copies the contents to an newly alloced
matrix. Returns NULL on failure*/
static char	**cpy_matrix(char **matrix)
{
	char	**ret;
	int		i;

	i = -1;
	if (!matrix)
		return (NULL);
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
			free_matrix(matrix);
			return (NULL);
		}
	}
	return (ret);
}
