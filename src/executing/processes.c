/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:45:13 by elisevanite       #+#    #+#             */
/*   Updated: 2024/05/23 17:33:46 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executing.h"

/* Set up all the pipes dependent on infile, outfile and pipes in the command.*/
static void	setup_pipes(int i, t_node *node, t_meta *meta)
{
	if (node->infile && node->infile[node->n_input - 1])
		dup2(node->fd_in[node->n_input - 1], STDIN_FILENO);
	else if (node->heredoc && node->heredoc[node->n_input - 1])
		dup2(node->hd_pipe[node->n_input - 1][0], STDIN_FILENO);
	else if (node->pipe_from_prev)
	{
		dup2(meta->pipe[i][0], STDIN_FILENO);
		ft_close(meta->pipe[i][1]);
		ft_close(meta->pipe[i][0]);
	}
	if (node->outfile && node->outfile[node->n_output - 1])
		dup2(node->fd_out[node->n_output - 1], STDOUT_FILENO);
	else if (node->pipe_to_next)
	{
		dup2(meta->pipe[i + 1][1], STDOUT_FILENO);
		ft_close(meta->pipe[i + 1][0]);
		ft_close(meta->pipe[i + 1][1]);

	}
}

/* Sets up the pipes, checks for buitlins
and executes command. Returns 0 if builtin was correctly executed,
or exits with 127 if the command was not correctly executed. */
static int	execute_cmnd(int i, t_node *node, t_meta *meta)
{
	int	builtin;

	setup_pipes(i, node, meta);
	builtin = check_builtin(node, meta);
	if (builtin == -1)
	{
		get_path(meta, node);
		if (execve(node->path, node->args, meta->envp) == -1)
			permission_checker(node->path, node, meta);
	}
	else
	{
		meta->exit_code = builtin;
		exit_error(NULL, NULL, meta->exit_code, meta);
	}
	return (EXIT_SUCCESS);
}

static int	check_signal(t_meta *meta)
{
	if (g_sig != 0)
	{
		free_array((void **)meta->pipe, meta->n_cmnds + 1);
		meta->pipe = NULL;
		return (1);
	}
	return (0);
}

/* Creates a pipe to the next command if necessary, forks to create a child
process, checks and opens the files, executes the command and finally closes the
 pipes in the parent.*/
void	child_process(int i, t_node *node, t_meta *meta)
{
	if (node->pipe_to_next)
	{
		meta->pipe[i + 1] = gnl_calloc(2, sizeof(int));
		if (pipe(meta->pipe[i + 1]) == -1)
			exit_error(ERR_PIPE, NULL, 1, meta);
	}
	check_heredoc(node, meta);
	if (check_signal(meta) == 1)
		return ;
	meta->pid[i] = fork();
	if (meta->pid[i] < 0)
		exit_error(ERR_CHILD, NULL, 1, meta);
	else if (meta->pid[i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (node->infile || node->outfile)
			open_files(node, meta);
		if (execute_cmnd(i, node, meta) != 0)
			exit_error(ERR_CMND, node->command, 127, meta);
	}
	else if (i > 0 && meta->pipe[i])
	{
		ft_close(meta->pipe[i][0]);
		ft_close(meta->pipe[i][1]);
	}
}
