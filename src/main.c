/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:22:18 by evan-ite          #+#    #+#             */
/*   Updated: 2024/05/15 17:01:59 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executing.h"
#include "../includes/parsing.h"

static char	**cpy_matrix(char **matrix);

int	g_sig = 0;

/*
char **envp:	An editable copy of the environment variables.
t_meta *meta:	empty meta struct

Initialize the meta struct. */
void	init_meta(t_meta *meta)
{
	meta->n_cmnds = 0;
	meta->pid = NULL;
	meta->pipe = NULL;
	meta->envp = cpy_matrix(__environ);
	meta->exit_code = 0;
	meta->cmnd_lst = NULL;
}

/*
Registers the Signals for SIGINT (ctrl+c) and SIGQUIT (ctrl+d) which is ignored
and runs by itself. ctrl+/ is not supposed to do anything.
Starts Minishell by creating an infinite while loop,
keeps prompting the user for input until user exits the program. */
int	main(void)
{
	char	*input;
	t_list	*cmnd_lst;
	t_meta	meta;

	cmnd_lst = NULL;
	init_meta(&meta);
	meta.cmnd_lst = &cmnd_lst;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
		input = readline("\x1b[1;35mminishell :) \x1b[0m");
		g_sig = 0;
		if (input && *input)
		{
			add_history(input);
			if (parse(input, &meta) == 0)
				execute(&meta);
			free(input);
		}
		else if (!input)
			exit_error(NULL, NULL, EXIT_SUCCESS, &meta);
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
			free_array((void **)matrix, -1);
			return (NULL);
		}
	}
	return (ret);
}
