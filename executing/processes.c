/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:45:13 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/15 15:53:30 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

static int	check_heredoc(t_node *node, t_meta *meta)
/* Returns 1 if the node contains a heredoc and arranges all input and output.
If there's no heredoc the function returns 0. */
{
	char	*line;
	char	*temp;
	int		i;

	if (!node->heredoc)
		return (0);
	node->hd_pipe = gnl_calloc(node->n_input, sizeof(int[2]));
	i = 0;
	while (i < node->n_input)
	{
		printf("yeas %s\n", node->heredoc[i]);
		if (node->heredoc[i])
		{
			if (pipe(node->hd_pipe[i]) == -1)
					exit_error(ERR_PIPE, NULL, 1, meta);
			while(1)
			{
				ft_putstr_fd("heredoc> ", STDOUT_FILENO);
				line = get_next_line(STDIN_FILENO);
				if (line == NULL)
				{
					ft_putstr_fd("warning: here-document delimited \
					by end-of-file\n", STDERR_FILENO);
					break ;
				}
				temp = remove_nl(line);
				if (!ft_strcmp(temp, node->heredoc[i]))
				{
					free(temp);
					break ;
				}
				free(temp);
				ft_putstr_fd(line, node->hd_pipe[i][1]);
				free(line);
			}
			ft_close(node->hd_pipe[i][1]);
		}
		i++;
		if (node->heredoc[i] && i < node->n_input)
			ft_close(node->hd_pipe[i - 1][0]);
	}
	return (1);
}

static void	setup_pipes(int i, t_node *node, t_meta *meta)
/* Set up all the pipes dependent on infile, outfile and pipes in the command.*/
{
	print_node(node);
	fprintf(stderr, "outfile %s and fd %i\n", node->outfile[node->n_output - 1], node->fd_out[node->n_output - 1]);
	if (node->infile && node->infile[node->n_input - 1])
		dup2(node->fd_in[node->n_input - 1], STDIN_FILENO);
	else if (node->heredoc && node->heredoc[node->n_input - 1])
		dup2(node->hd_pipe[node->n_input - 1][0], STDIN_FILENO);
	else if (node->pipe_from_prev)
	{
		dup2(meta->pipe[i][0], STDIN_FILENO);
		ft_close(meta->pipe[i][1]);
	}
	if (node->outfile && node->outfile[node->n_output - 1])
		dup2(node->fd_out[node->n_output - 1], STDOUT_FILENO);
	else if (node->pipe_to_next)
	{
		dup2(meta->pipe[i + 1][1], STDOUT_FILENO);
		ft_close(meta->pipe[i + 1][0]);
	}
	printf("TEST\n");
}

static int	execute_cmnd(int i, t_node *node, t_meta *meta)
/* Sets up the pipes, checks for buitlins
and executes command. Returns 0 if builtin was correctly executed,
or exits with 127 if the command was not correctly executed. */
{
	int	builtin;

	setup_pipes(i, node, meta);
	builtin = check_builtin(node, meta);
	if (builtin == -1)
	{
		get_path(i, meta, node);
		if (execve(node->path, node->args, meta->envp) == -1)
			exit_error(ERR_CMND, node->command, 127, meta);
	}
	else
		exit(builtin);
	return (EXIT_SUCCESS);
}

void	child_process(int i, t_node *node, t_meta *meta)
/* Creates a pipe to the next command if necessary, forks to create a child process,
checks and opens the files, executes the command and finally closes the pipes in the parent.*/
{
	if (node->pipe_to_next)
	{
		meta->pipe[i + 1] = gnl_calloc(2, sizeof(int));
		if (pipe(meta->pipe[i + 1]) == -1)
			exit_error(ERR_PIPE, NULL, 1, meta);
	}
	check_heredoc(node, meta);
	meta->pid[i] = fork();
	if (meta->pid[i] < 0)
		exit_error(ERR_CHILD, NULL, 1, meta);
	else if (meta->pid[i] == 0)
	{
		// print_node(node);
		if (node->infile || node->outfile)
			open_files(node, meta);
		if (execute_cmnd(i, node, meta) != 0)
			exit_error(ERR_CMND, node->command, 127, meta);
	}
	else
	{
		if (i > 0)
		{
			ft_close(meta->pipe[i][0]);
			ft_close(meta->pipe[i][1]);
		}
	}
}
