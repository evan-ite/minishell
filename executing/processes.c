/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:45:13 by elisevanite       #+#    #+#             */
/*   Updated: 2024/04/15 11:20:44 by evan-ite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

static int	set_heredoc(t_node *node, t_meta *meta)
/* Returns 1 if the node contains a heredoc and arranges all input and output.
If there's no heredoc the function returns 0. */
{
	// pid_t	pid;
	char	*line;
	char	*temp;

	if (!node->heredoc)
		return (0);
	if (pipe(node->hd_pipe) == -1)
			exit_error(ERR_PIPE, NULL, 1, meta);
	// pid = fork();
	// if (pid == 0)
	// {
		// ft_close(node->hd_pipe[0]);
		while(1)
		{
			line = get_next_line(STDIN_FILENO);
			temp = remove_nl(line);
			if (!ft_strcmp(temp, node->heredoc))
			{
				free(temp);
				break ;
			}
			free(temp);
			ft_putstr_fd(line, node->hd_pipe[1]);
		}
	// }
	// else
	// {
	// 	ft_close(node->hd_pipe[1]);
		dup2(node->hd_pipe[0], STDIN_FILENO);
	// 	wait(NULL);
	// }
	return (1);
}

static void	setup_pipes(int i, t_node *node, t_meta *meta)
/* Set up all the pipes dependent on infile, outfile and pipes in the command.*/
{
	if (node->infile)
		dup2(node->fd_in, STDIN_FILENO);
	else if (node->heredoc)
		set_heredoc(node, meta);
	else if (node->pipe_from_prev)
	{
		dup2(meta->pipe[i][0], STDIN_FILENO);
		ft_close(meta->pipe[i][1]);
	}
	if (node->outfile)
		dup2(node->fd_out, STDOUT_FILENO);
	else if (node->pipe_to_next)
	{
		dup2(meta->pipe[i + 1][1], STDOUT_FILENO);
		ft_close(meta->pipe[i + 1][0]);
	}
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
	meta->pid[i] = fork();
	if (meta->pid[i] < 0)
		exit_error(ERR_CHILD, NULL, 1, meta);
	else if (meta->pid[i] == 0)
	{
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
